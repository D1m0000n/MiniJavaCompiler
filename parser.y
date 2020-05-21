%skeleton "lalr1.cc"
%require "3.5"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    class Scanner;
    class Driver;

    #include "visitors/forward_decl.h"
}

// %param { Driver &drv }

%define parse.trace
%define parse.error verbose

%code {
    #include "driver.hh"
    #include "location.hh"

    #include "visitors/elements.h"

    static yy::parser::symbol_type yylex(Scanner &scanner, Driver& driver) {
        return scanner.ScanToken();
    }
}

%lex-param { Scanner &scanner }
%lex-param { Driver &driver }
%parse-param { Scanner &scanner }
%parse-param { Driver &driver }

%locations

%define api.token.prefix {TOK_}

%token
    END 0 "end of file"
    ASSIGN "="
    MINUS "-"
    PLUS "+"
    STAR "*"
    SLASH "/"
    LPAREN "("
    RPAREN ")"
    PRINT "System.out.println"
    INT "int"
    LEFTSCOPE "{"
    RIGHTSCOPE "}"
    SEMICOLON ";"
    LESS "<"
    GREATER ">"
    MODULO "%"
    AND "&&"
    OR "||"
    ISEQUAL "=="
    CLASS "class"
    PUBLIC "public"
    STATIC "static"
    VOID "void"
    MAIN "main"
    IF "if"
    ELSE "else"
    WHILE "while"
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%nterm <Expression*> exp
%nterm <Statement*> statement
%nterm <AssignmentList*> statements
%nterm <Program*> unit
%nterm <MainClass*> main_class
%nterm <Program*> program

// %printer { yyo << $$; } <*>;

%%
%start unit;

unit: program { $$ = $1; driver.program = $1; };

program:
    main_class {$$ = new Program($1); }

main_class:
    "class" "identifier" "{" "public" "static" "void" "main" "(" ")" "{" statements "}" "}"
    {$$ = new MainClass($2, $11); }

statements:
    %empty { $$ = new AssignmentList(); /* A -> eps */}
    | statements statement {
        $1->AddStatement($2); $$ = $1;
    };

statement:
    "identifier" "=" exp ";" { $$ = new Assignment($1, $3);}
    | "System.out.println" "(" exp ")" ";" { $$ = new PrintStatement($3); }
    | "int" "identifier" ";" { $$ = new VarDecl($2); }
    | "{" statements "}" { $$ = new ScopeAssignmentList($2); }
    | "if" "(" exp ")" statements {$$ = new IfStatement($3, $5, NULL); }
    | "if" "(" exp ")" statements "else" statements {$$ = new IfStatement($3, $5, $7); }
    | "while" "(" exp ")" statements {$$ = new WhileStatement($3, $5); }
    ;

%left "+" "-";
%left "*" "/";

exp:
    "number" {$$ = new NumberExpression($1); }
    | "identifier" {$$ = new IdentExpression($1); }
    | exp "+" exp { $$ = new AddExpression($1, $3); }
    | exp "-" exp { $$ = new SubtractExpression($1, $3); }
    | exp "*" exp { $$ = new MulExpression($1, $3); }
    | exp "/" exp { $$ = new DivExpression($1, $3); }
    | exp "<" exp { $$ = new IsLessExpression($1, $3); }
    | exp ">" exp { $$ = new IsGreaterExpression($1, $3); }
    | exp "==" exp {$$ = new IsEqualExpression($1, $3); }
    | exp "&&" exp {$$ = new AndExpression($1, $3); }
    | exp "||" exp {$$ = new OrExpression($1, $3); }
    | exp "%" exp {$$ = new ModuloExpression($1, $3); }
    | "(" exp ")" { $$ = $2; };

%%

void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
