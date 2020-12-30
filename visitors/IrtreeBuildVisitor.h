#pragma once

#include <include/visitors/Visitor.h>
#include <irtree/tree_wrapper/SubtreeWrapper.h>
#include <unordered_map>
#include <function-mechanisms/FrameTranslator.h>
#include <symbol_table/ScopeLayerTree.h>
#include "TemplateVisitor.h"

using IrtMapping = std::unordered_map<std::string, IRT::Statement*>;

class IrtreeBuildVisitor : public TemplateVisitor<IRT::SubtreeWrapper*> {
 public:
  explicit IrtreeBuildVisitor(ScopeLayerTree* layer_tree);
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

  void Visit(ThisExpression* this_expression) override;

  void Visit(MainClass* main_class) override;

  IrtMapping GetTrees();

  void SetMainFunction(Function* main_func);

 private:
  std::unordered_map<std::string, IRT::FrameTranslator*> frame_translator_;

  IRT::FrameTranslator* current_frame_;
  ScopeLayerTree* tree_;

  std::string this_;
  Function* main_function_;
  IrtMapping method_trees_;
};


