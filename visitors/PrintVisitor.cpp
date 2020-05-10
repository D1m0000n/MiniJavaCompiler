#include "PrintVisitor.h"

#include "elements.h"

#include <iostream>

SymbolTreeVisitor::SymbolTreeVisitor(const std::string& filename) : stream_(filename) {
}

void SymbolTreeVisitor::Visit(NumberExpression* expression) {
  PrintTabs();
  stream_ << "NumExpression " << expression->value_ << std::endl;
}

void SymbolTreeVisitor::Visit(AddExpression* expression) {
  PrintTabs();
  stream_ << "AddExpression is:" << std::endl;

  ++num_tabs_;
  expression->first->AcceptVisitor(this);
  expression->second->AcceptVisitor(this);
  --num_tabs_;
}

void SymbolTreeVisitor::Visit(SubtractExpression* expression) {
  PrintTabs();

  stream_ << "SubExpression: " << std::endl;
  ++num_tabs_;
  expression->first->AcceptVisitor(this);
  expression->second->AcceptVisitor(this);
  --num_tabs_;
}

void SymbolTreeVisitor::Visit(MulExpression* expression) {
  PrintTabs();

  stream_ << "MulExpression: " << std::endl;
  ++num_tabs_;
  expression->first->AcceptVisitor(this);
  expression->second->AcceptVisitor(this);
  --num_tabs_;
}

void SymbolTreeVisitor::Visit(DivExpression* expression) {
  PrintTabs();
  stream_ << "DivExpression: " << std::endl;
  ++num_tabs_;
  expression->first->AcceptVisitor(this);
  expression->second->AcceptVisitor(this);
  --num_tabs_;
}

void SymbolTreeVisitor::Visit(AndExpression* expression) {
  PrintTabs();
  stream_ << "AndExpression: " << std::endl;
  ++num_tabs_;
  expression->first->AcceptVisitor(this);
  expression->second->AcceptVisitor(this);
  --num_tabs_;
}

void SymbolTreeVisitor::Visit(OrExpression* expression) {
  PrintTabs();
  stream_ << "AndExpression: " << std::endl;
  ++num_tabs_;
  expression->first->AcceptVisitor(this);
  expression->second->AcceptVisitor(this);
  --num_tabs_;
}

void SymbolTreeVisitor::Visit(ModuloExpression* expression) {
  PrintTabs();
  stream_ << "ModuloExpression: " << std::endl;
  ++num_tabs_;
  expression->first->AcceptVisitor(this);
  expression->second->AcceptVisitor(this);
  --num_tabs_;
}

void SymbolTreeVisitor::Visit(IsEqualExpression* expression) {
  PrintTabs();
  stream_ << "IsEqualExpression: " << std::endl;
  ++num_tabs_;
  expression->first->AcceptVisitor(this);
  expression->second->AcceptVisitor(this);
  --num_tabs_;
}

void SymbolTreeVisitor::Visit(IsLessExpression* expression) {
  PrintTabs();
  stream_ << "IsLessExpression: " << std::endl;
  ++num_tabs_;
  expression->first->AcceptVisitor(this);
  expression->second->AcceptVisitor(this);
  --num_tabs_;
}

void SymbolTreeVisitor::Visit(IsGreaterExpression* expression) {
  PrintTabs();
  stream_ << "IsGreaterExpression: " << std::endl;
  ++num_tabs_;
  expression->first->AcceptVisitor(this);
  expression->second->AcceptVisitor(this);
  --num_tabs_;
}

void SymbolTreeVisitor::Visit(IdentExpression* expression) {
  PrintTabs();

  stream_ << "IdentExpression: " << expression->ident_ << std::endl;
}

void SymbolTreeVisitor::Visit(Assignment* assignment) {
  PrintTabs();
  stream_ << "Assignment: " << assignment->variable_ << std::endl;
  ++num_tabs_;
  assignment->expression_->AcceptVisitor(this);
  --num_tabs_;
}

void SymbolTreeVisitor::Visit(AssignmentList* assignment_list) {
  PrintTabs();
  stream_ << "AssignmentList: " << std::endl;

  ++num_tabs_;
  for (Assignment* assignment : assignment_list->assignments_) {
    assignment->AcceptVisitor(this);
  }
  --num_tabs_;
}

void SymbolTreeVisitor::Visit(Program* program) {
  stream_ << "Program:" << std::endl;

  ++num_tabs_;

  program->assignments_->AcceptVisitor(this);
  program->expression_->AcceptVisitor(this);

  --num_tabs_;
}

void SymbolTreeVisitor::PrintTabs() {
  for (int i = 0; i < num_tabs_; ++i) {
    stream_ << '\t';
  }
}

SymbolTreeVisitor::~SymbolTreeVisitor() {
  stream_.close();
}