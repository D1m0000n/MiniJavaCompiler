#include "PrintVisitor.h"

#include "elements.h"

#include <iostream>

PrintVisitor::PrintVisitor(const std::string& filename) : stream_(filename) {
}

void PrintVisitor::Visit(NumberExpression* expression) {
  PrintTabs();
  stream_ << "NumExpression " << expression->value_ << std::endl;
}

void PrintVisitor::Visit(AddExpression* expression) {
  PrintTabs();
  stream_ << "AddExpression is:" << std::endl;

  ++num_tabs_;
  expression->first->Accept(this);
  expression->second->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(SubtractExpression* expression) {
  PrintTabs();

  stream_ << "SubExpression: " << std::endl;
  ++num_tabs_;
  expression->first->Accept(this);
  expression->second->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(MulExpression* expression) {
  PrintTabs();

  stream_ << "MulExpression: " << std::endl;
  ++num_tabs_;
  expression->first->Accept(this);
  expression->second->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(DivExpression* expression) {
  PrintTabs();
  stream_ << "DivExpression: " << std::endl;
  ++num_tabs_;
  expression->first->Accept(this);
  expression->second->Accept(this);
  --num_tabs_;
}

////

void PrintVisitor::Visit(AndExpression* expression) {
  PrintTabs();
  stream_ << "AndExpression: " << std::endl;
  ++num_tabs_;
  expression->first->Accept(this);
  expression->second->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(IsEqualExpression* expression) {
  PrintTabs();
  stream_ << "IsEqualExpression: " << std::endl;
  ++num_tabs_;
  expression->first->Accept(this);
  expression->second->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(IsLessExpression* expression) {
  PrintTabs();
  stream_ << "IsLessExpression: " << std::endl;
  ++num_tabs_;
  expression->first->Accept(this);
  expression->second->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(IsGreaterExpression* expression) {
  PrintTabs();
  stream_ << "IsGreaterExpression: " << std::endl;
  ++num_tabs_;
  expression->first->Accept(this);
  expression->second->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(ModuloExpression* expression) {
  PrintTabs();
  stream_ << "ModuloExpression: " << std::endl;
  ++num_tabs_;
  expression->first->Accept(this);
  expression->second->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(OrExpression* expression) {
  PrintTabs();
  stream_ << "OrExpression: " << std::endl;
  ++num_tabs_;
  expression->first->Accept(this);
  expression->second->Accept(this);
  --num_tabs_;
}

////

void PrintVisitor::Visit(IdentExpression* expression) {
  PrintTabs();

  stream_ << "IdentExpression: " << expression->ident_ << std::endl;
}

void PrintVisitor::Visit(Assignment* assignment) {
  PrintTabs();
  stream_ << "Assignment: " << assignment->variable_ << std::endl;
  ++num_tabs_;
  assignment->expression_->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(VarDecl* var_decl) {
  PrintTabs();
  stream_ << "VarDecl: " << var_decl->variable_ << std::endl;
}

void PrintVisitor::Visit(MethodDecl* method_decl) {
  PrintTabs();
  stream_ << "MethodDecl: " << std::endl;
}

void PrintVisitor::Visit(ClassDecl* class_decl) {
  PrintTabs();
  stream_ << "ClassDecl: " << class_decl->identifier << std::endl;
  ++num_tabs_;
  class_decl->declaration_list_->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(DeclarationList* declaration_list) {
  PrintTabs();
  stream_ << "Declaration list: " << std::endl;
  ++num_tabs_;
  for (Declaration* declaration : declaration_list->declarations_) {
    declaration->Accept(this);
  }
  --num_tabs_;
}

void PrintVisitor::Visit(PrintStatement* statement) {
  PrintTabs();
  stream_ << "PrintStatement: " << std::endl;
  ++num_tabs_;
  statement->expression_->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(AssignmentList* assignment_list) {
  PrintTabs();
  stream_ << "AssignmentList: " << std::endl;

  ++num_tabs_;
  for (Statement* assignment : assignment_list->statements_) {
    assignment->Accept(this);
  }
  --num_tabs_;
}

void PrintVisitor::Visit(ScopeAssignmentList* list) {
  stream_ << "ScopeAssignmentList:" << std::endl;
  ++num_tabs_;

  list->statement_list->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(IfStatement* if_statement) {
  stream_ << "IfStatement:" << std::endl;
  ++num_tabs_; // ???
  if_statement->expression_->Accept(this);

  --num_tabs_;
}

void PrintVisitor::Visit(WhileStatement* while_statement) {
  stream_ << "WhileStatement:" << std::endl;
  ++num_tabs_; // ???
}

void PrintVisitor::Visit(Program* program) {
  stream_ << "Program:" << std::endl;

  ++num_tabs_;

  program->main_class_->Accept(this);
//    program->expression_->Accept(this);

  --num_tabs_;
}

void PrintVisitor::Visit(MainClass* main_class) {
  stream_ << "Main class:" << std::endl;

  ++num_tabs_;
  main_class->statements_->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(Function* function) {
  PrintTabs();
  stream_ << "Function:" << std::endl;

  ++num_tabs_;

  PrintTabs();
  stream_ << "Name: " << function->name_ << std::endl;
  function->param_list_->Accept(this);
  function->statements_->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(ParamList* param_list) {
  PrintTabs();
  stream_ << "ParamList:" << std::endl;

  ++num_tabs_;

  for (const std::string& param: param_list->params_) {
    PrintTabs();
    stream_ << param << std::endl;
  }
  --num_tabs_;
}

void PrintVisitor::Visit(FunctionList* function_list) {
  PrintTabs();
  stream_ << "FunctionList:" << std::endl;

  ++num_tabs_;
  for (auto* function: function_list->functions_) {
    function->Accept(this);
  }
  --num_tabs_;
}

void PrintVisitor::Visit(ParamValueList* param_value_list) {
  PrintTabs();
  stream_ << "ParamValueList:" << std::endl;

  ++num_tabs_;

  for (Expression* param: param_value_list->params_) {;
    param->Accept(this);
//        stream_ << param << std::endl;
  }
  --num_tabs_;
}

void PrintVisitor::Visit(FunctionCallExpression* statement) {
  PrintTabs();
  stream_ << "CallStatement:" << std::endl;
  ++num_tabs_;

  PrintTabs();
  stream_ << "Name: " << statement->name_ << std::endl;
  statement->param_list_->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(ReturnStatement* return_statement) {
  PrintTabs();
  stream_ << "ReturnStatement:" << std::endl;

  ++num_tabs_;
  return_statement->return_expression_->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(ThisExpression* this_expression) {
  PrintTabs();
  stream_ << "Found this " << std::endl;
}

void PrintVisitor::PrintTabs() {
  for (int i = 0; i < num_tabs_; ++i) {
    stream_ << '\t';
  }
}

PrintVisitor::~PrintVisitor() {
  stream_.close();
}