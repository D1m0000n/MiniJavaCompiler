#include "SymbolTreeVisitor.h"

#include "elements.h"

#include <iostream>

#include "objects/Integer.h"

SymbolTreeVisitor::SymbolTreeVisitor() : tree_(new ScopeLayer) {

  tree_.root_->DeclareVariable(Symbol("true"));
  tree_.root_->DeclareVariable(Symbol("false"));

  tree_.root_->Put(Symbol("true"), std::make_shared<Integer>(1));
  tree_.root_->Put(Symbol("false"), std::make_shared<Integer>(0));

  current_layer_ = tree_.root_;

//    path_.push_back(tree_.root_);
}

void SymbolTreeVisitor::Visit(NumberExpression* expression) {
}

void SymbolTreeVisitor::Visit(AddExpression* expression) {
}

void SymbolTreeVisitor::Visit(SubtractExpression* expression) {
}

void SymbolTreeVisitor::Visit(MulExpression* expression) {
}

void SymbolTreeVisitor::Visit(DivExpression* expression) {
}
///

void SymbolTreeVisitor::Visit(AndExpression* expression) {
}

void SymbolTreeVisitor::Visit(IsEqualExpression* expression) {
}

void SymbolTreeVisitor::Visit(IsLessExpression* expression) {
}

void SymbolTreeVisitor::Visit(IsGreaterExpression* expression) {
}

void SymbolTreeVisitor::Visit(ModuloExpression* expression) {
}

void SymbolTreeVisitor::Visit(OrExpression* expression) {
}

////
void SymbolTreeVisitor::Visit(IdentExpression* expression) {
}

void SymbolTreeVisitor::Visit(Assignment* assignment) {

}

void SymbolTreeVisitor::Visit(PrintStatement* statement) {
}

void SymbolTreeVisitor::Visit(AssignmentList* assignment_list) {
  for (Statement* assignment: assignment_list->statements_) {
    assignment->Accept(this);
  }
}

void SymbolTreeVisitor::Visit(VarDecl* var_decl) {
  std::cout << "Declaring var " << var_decl->variable_ << std::endl;
  current_layer_->DeclareVariable(Symbol(var_decl->variable_));
}

void SymbolTreeVisitor::Visit(ScopeAssignmentList* list) {
  auto new_layer = new ScopeLayer(current_layer_);

  current_layer_ = new_layer;
  list->statement_list->Accept(this);
  current_layer_ = current_layer_->GetParent();
}

void SymbolTreeVisitor::Visit(IfStatement* if_statement) {
  if_statement->true_statement_->Accept(this);
  if (if_statement->false_statement_) {
    if_statement->false_statement_->Accept(this);
  }
}

void SymbolTreeVisitor::Visit(WhileStatement* while_statement) {
  while_statement->statement_->Accept(this);
}

void SymbolTreeVisitor::Visit(Program* program) {
  if (program == nullptr) {
    throw std::runtime_error("Syntax error");
  }
  program->main_class_->Accept(this);
//    program->expression_->Accept(this); // tos value is called
}

void SymbolTreeVisitor::Visit(MainClass* main_class) {
  main_class->statement_->Accept(this);
}

ScopeLayer* SymbolTreeVisitor::GetRoot() {
  return current_layer_;
}