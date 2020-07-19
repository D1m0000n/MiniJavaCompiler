#pragma once
#include "TemplateVisitor.h"

#include "symbol_table/Table.h"
#include <map>

#include "symbol_table/ScopeLayerTree.h"
#include <BinaryExpression.h>

class TypeCheckerVisitor : public TemplateVisitor<std::string> {
 public:
  explicit TypeCheckerVisitor(ScopeLayerTree* root);

  void Visit(NumberExpression* expression) override;
  void Visit(AddExpression* expression) override;
  void Visit(SubtractExpression* expression) override;
  void Visit(MulExpression* expression) override;
  void Visit(DivExpression* expression) override;
  void Visit(IdentExpression* expression) override;
  void Visit(Assignment* assignment) override;
  void Visit(PrintStatement* statement) override;
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

  void Visit(VarDecl* var_decl) override;
  void Visit(ClassDecl* class_decl) override;
  void Visit(MethodDecl* method_decl) override;
  void Visit(DeclarationList* declaration_list) override;

  void Visit(Function* function) override;
  void Visit(FunctionList* function_list) override;
  void Visit(ParamList* param_list) override;
  void Visit(ParamValueList* param_value_list) override;

  void Visit(FunctionCallExpression* statement) override;
  void Visit(ReturnStatement* statement) override;

  void Visit(MainClass* main_class) override;

  void Visit(ThisExpression* this_expression) override;


  void CheckTypes(Program* program);

 private:

  void BinaryTypesCheck(BinaryExpression* expression, const std::string& name);

  ScopeLayerTree* tree_;
  ScopeLayer* current_layer_;
  std::stack<int> offsets_;
  std::string this_;
};
