#pragma once

#include "Visitor.h"

#include <fstream>
#include <string>

class SymbolTreeVisitor : public Visitor {
 public:
  SymbolTreeVisitor(const std::string& filename);
  ~SymbolTreeVisitor();
  void Visit(NumberExpression* expression) override;
  void Visit(AddExpression* expression) override;
  void Visit(SubtractExpression* expression) override;
  void Visit(AndExpression* expression) override;
  void Visit(OrExpression* expression) override;
  void Visit(ModuloExpression* expression) override;
  void Visit(IsEqualExpression* expression) override;
  void Visit(IsLessExpression* expression) override;
  void Visit(IsGreaterExpression* expression) override;
  void Visit(MulExpression* expression) override;
  void Visit(DivExpression* expression) override;
  void Visit(IdentExpression* expression) override;
  void Visit(Assignment* assignment) override;
  void Visit(AssignmentList* assignment_list) override;
  void Visit(Program* program) override;
 private:

  void PrintTabs();
  std::ofstream stream_;
  int num_tabs_ = 0;

};
