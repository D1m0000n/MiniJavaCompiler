#pragma once

#include "forward_decl.h"

class Visitor {
 public:
  virtual void Visit(NumberExpression* expression) = 0;
  virtual void Visit(AddExpression* expression) = 0;
  virtual void Visit(SubtractExpression* expression) = 0;
  virtual void Visit(MulExpression* expression) = 0;
  virtual void Visit(DivExpression* expression) = 0;
  virtual void Visit(IdentExpression* expression) = 0;
  virtual void Visit(Assignment* assignment) = 0;
  virtual void Visit(PrintStatement* statement) = 0;
  virtual void Visit(AssignmentList* assignment_list) = 0;
  virtual void Visit(ScopeAssignmentList* list) = 0;
  virtual void Visit(Program* program) = 0;

  virtual void Visit(AndExpression* expression) = 0;
  virtual void Visit(IsEqualExpression* expression) = 0;
  virtual void Visit(IsGreaterExpression* expression) = 0;
  virtual void Visit(IsLessExpression* expression) = 0;
  virtual void Visit(ModuloExpression* expression) = 0;
  virtual void Visit(OrExpression* expression) = 0;

  virtual void Visit(IfStatement* if_statement) = 0;
  virtual void Visit(WhileStatement* while_statement) = 0;

  virtual void Visit(VarDecl* var_decl) = 0;
  virtual void Visit(ClassDecl* class_decl) = 0;
  virtual void Visit(MethodDecl* method_decl) = 0;
  virtual void Visit(DeclarationList* declaration_list) = 0;

  virtual void Visit(MainClass* main_class) = 0;
};
