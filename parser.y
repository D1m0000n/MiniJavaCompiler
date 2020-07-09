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

    #include "include/visitors/forward_decl.h"
}

// %param { Driver &drv }

%define parse.trace
%define parse.error verbose

%code {
    #include "include/driver.hh"
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
%nterm <Statement*> local_variable_declaration
%nterm <AssignmentList*> statements

%nterm <Program*> unit
%nterm <MainClass*> main_class
%nterm <Program*> program

%nterm <Declaration*> declaration
%nterm <Declaration*> variable_declaration
%nterm <Declaration*> method_declaration
%nterm <Declaration*> class_declaration
%nterm <DeclarationList*> declarations
%nterm <DeclarationList*> class_declarations

%nterm <std::string> simple_type
%nterm <std::string> type
%nterm <std::string> type_identifier

// %printer { yyo << $$; } <*>;

%%
%start unit;

unit: program { $$ = $1; driver.program = $1; };

program:
    main_class class_declarations {$$ = new Program($1, $2); }

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
    | local_variable_declaration { $$ = $1; }
    | "System.out.println" "(" exp ")" ";" { $$ = new PrintStatement($3); }
    | "{" statements "}" { $$ = new ScopeAssignmentList($2); }
    | "if" "(" exp ")" statements {$$ = new IfStatement($3, $5, NULL); }
    | "if" "(" exp ")" statements "else" statements {$$ = new IfStatement($3, $5, $7); }
    | "while" "(" exp ")" statements {$$ = new WhileStatement($3, $5); }
    ;

local_variable_declaration:
    variable_declaration { $$ = reinterpret_cast<Statement*>($1); }

class_declarations:
    %empty { $$ = new DeclarationList(); }
    | class_declarations class_declaration {
      $1->AddDeclaration($2); $$ = $1;
    };

class_declaration:
    "class" "identifier" "{" declarations "}" {
      $$ = new ClassDecl($2, $4);
    }

declarations:
    %empty {$$ = new DeclarationList(); }
    | declarations declaration {
      $1->AddDeclaration($2); $$ = $1;
    };

declaration:
    variable_declaration { $$ = $1; }
    | method_declaration { $$ = $1; }

type:
    simple_type { $$ = $1; }

simple_type:
    "int" {$$ = "int"; }
    | "boolean" { $$ = "boolean"; }
    | "void" { $$ = "void"; }
    | type_identifier { $$ = $1; }

type_identifier:
    "identifier" { $$ = $1; }

variable_declaration:
    type "identifier" ";" { $$ = new VarDecl($1, $2); }

method_declaration:
    "public" type "identifier" ";" {$$ = new MethodDecl($2, $3); }

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
