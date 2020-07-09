#pragma once

#include "include/visitors/Visitor.h"

#include <fstream>
#include <string>

class PrintVisitor : public Visitor {
 public:
  PrintVisitor(const std::string& filename);
  ~PrintVisitor();
  void Visit(NumberExpression* expression) override;
  void Visit(AddExpression* expression) override;
  void Visit(SubtractExpression* expression) override;
  void Visit(MulExpression* expression) override;
  void Visit(DivExpression* expression) override;
  void Visit(IdentExpression* expression) override;
  void Visit(PrintStatement* statement) override;
  void Visit(Assignment* assignment) override;
  void Visit(AssignmentList* assignment_list) override;
  void Visit(ScopeAssignmentList* list) override;
  void Visit(Program* program) override;

  void Visit(AndExpression* expression) override;
  void Visit(IsEqualExpression* expression) override;
  void Visit(IsGreaterExpression* expression) override;
  void Visit(IsLessExpression* expression) override;
  void Visit(ModuloExpression* expression) override;
  void Visit(OrExpression* expression) override;
  void Visit(IfStatement* if_statement) override;
  void Visit(WhileStatement* while_statement) override;

  void Visit(VarDecl* declaration) override;
  void Visit(ClassDecl* declaration) override;
  void Visit(DeclarationList* declaration_list) override;
  void Visit(MethodDecl* method_decl) override;

  void Visit(Function* function) override;
  void Visit(FunctionList* function_list) override;
  void Visit(ParamList* param_list) override;
  void Visit(ParamValueList* param_value_list) override;

  void Visit(MainClass* main_class) override;

 private:

  void PrintTabs();
  std::ofstream stream_;
  int num_tabs_ = 0;

};
