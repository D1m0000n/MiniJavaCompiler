#include "SymbolTreeVisitor.h"

#include "elements.h"

#include <iostream>

#include "objects/Integer.h"

SymbolTreeVisitor::SymbolTreeVisitor() : tree_(new ScopeLayer) {

//  tree_.root_->DeclareVariable(Symbol("true"), "int");
//  tree_.root_->DeclareVariable(Symbol("false"), "int");

//  tree_.root_->Put(Symbol("true"), std::make_shared<Integer>(1));
//  tree_.root_->Put(Symbol("false"), std::make_shared<Integer>(0));

  current_layer_ = tree_.root_;

//    path_.push_back(tree_.root_);
}

void SymbolTreeVisitor::Visit(NumberExpression* expression) {
}

void SymbolTreeVisitor::Visit(AddExpression* expression) {
  expression->first->Accept(this);
  expression->second->Accept(this);
}

void SymbolTreeVisitor::Visit(SubtractExpression* expression) {
  expression->first->Accept(this);
  expression->second->Accept(this);
}

void SymbolTreeVisitor::Visit(MulExpression* expression) {
  expression->first->Accept(this);
  expression->second->Accept(this);
}

void SymbolTreeVisitor::Visit(DivExpression* expression) {
  expression->first->Accept(this);
  expression->second->Accept(this);
}

void SymbolTreeVisitor::Visit(AndExpression* expression) {
  expression->first->Accept(this);
  expression->second->Accept(this);
}

void SymbolTreeVisitor::Visit(IsEqualExpression* expression) {
  expression->first->Accept(this);
  expression->second->Accept(this);
}

void SymbolTreeVisitor::Visit(IsLessExpression* expression) {
  expression->first->Accept(this);
  expression->second->Accept(this);
}

void SymbolTreeVisitor::Visit(IsGreaterExpression* expression) {
  expression->first->Accept(this);
  expression->second->Accept(this);
}

void SymbolTreeVisitor::Visit(ModuloExpression* expression) {
  expression->first->Accept(this);
  expression->second->Accept(this);
}

void SymbolTreeVisitor::Visit(OrExpression* expression) {
  expression->first->Accept(this);
  expression->second->Accept(this);
}

void SymbolTreeVisitor::Visit(IdentExpression* expression) {
  current_layer_->Get(Symbol(expression->ident_)); // check that element exists
}

void SymbolTreeVisitor::Visit(Assignment* assignment) {
  current_layer_->Get(assignment->variable_);

  assignment->expression_->Accept(this);
}

void SymbolTreeVisitor::Visit(PrintStatement* statement) {
  statement->expression_->Accept(this);
}

void SymbolTreeVisitor::Visit(AssignmentList* assignment_list) {
  for (Statement* assignment: assignment_list->statements_) {
    assignment->Accept(this);
  }
}

void SymbolTreeVisitor::Visit(VarDecl* var_decl) {
  std::cout << "Declaring var " << var_decl->variable_ << std::endl;
  current_layer_->DeclareVariable(Symbol(var_decl->variable_), var_decl->type_);
}

void SymbolTreeVisitor::Visit(ClassDecl* class_decl) {
  this_ = class_decl->identifier;

  std::cout << "Declaring class " << class_decl->identifier << std::endl;
  class_decl->declaration_list_->Accept(this);
}

void SymbolTreeVisitor::Visit(MethodDecl* method_decl) {
  std::cout << "Declaring method " << method_decl->identifier_ << std::endl;
  method_decl->assignment_list_->Accept(this);
}

void SymbolTreeVisitor::Visit(DeclarationList* declaration_list) {
  for (Declaration* declaration : declaration_list->declarations_) {
    declaration->Accept(this);
  }
}

void SymbolTreeVisitor::Visit(ScopeAssignmentList* list) {
  auto new_layer = new ScopeLayer(current_layer_);

  current_layer_ = new_layer;
  list->statement_list->Accept(this);
  current_layer_ = current_layer_->GetParent();
}

void SymbolTreeVisitor::Visit(IfStatement* if_statement) {
//  if_statement->true_statement_->Accept(this);
  if_statement->expression_->Accept(this);
  auto true_layer = new ScopeLayer(current_layer_);
  current_layer_ = true_layer;

  if_statement->true_statement_->Accept(this);
  current_layer_ = current_layer_->GetParent();

  auto false_layer = new ScopeLayer(current_layer_);
  current_layer_ = false_layer;

  if (if_statement->false_statement_) {
    if_statement->false_statement_->Accept(this);
  }
  current_layer_ = current_layer_->GetParent();

//  if (if_statement->false_statement_) {
//    if_statement->false_statement_->Accept(this);
//  }
}

void SymbolTreeVisitor::Visit(WhileStatement* while_statement) {
  while_statement->expression_->Accept(this);

  auto while_layer = new ScopeLayer(current_layer_);
  current_layer_ = while_layer;

  while_statement->statement_->Accept(this);
  current_layer_ = current_layer_->GetParent();
}

void SymbolTreeVisitor::Visit(Function* function) {
  std::string full_func_name = this_ + "." + function->name_;

  current_layer_->DeclareFunction(Symbol(function->name_), function);

  auto new_layer = new ScopeLayer(current_layer_);

  current_layer_ = new_layer;

  function->param_list_->Accept(this);
  function->statements_->Accept(this);

  tree_.AddMapping(Symbol(function->name_), new_layer);

  current_layer_ = current_layer_->GetParent();

  functions_[Symbol(function->name_)] = function;
}

void SymbolTreeVisitor::Visit(FunctionList* function_list) {
  for (auto* function : function_list->functions_) {
    function->Accept(this);
  }
}

void SymbolTreeVisitor::Visit(ParamValueList* value_list) {
  for (Expression* value : value_list->params_) {
    value->Accept(this);
  }
}

void SymbolTreeVisitor::Visit(ParamList *param_list) {
  for (size_t i = 0; i < param_list->params_.size(); ++i) {
    const std::string& param = param_list->params_[i];
    const std::string& type = param_list->types_[i];
    current_layer_->DeclareVariable(Symbol(param), type);
  }
//  for (const std::string& param: param_list->params_) {
//    current_layer_->DeclareVariable(Symbol(param), "int"); //// check for type
//  }
}

void SymbolTreeVisitor::Visit(FunctionCallExpression* statement) {
  // We don't check function name because function could be created after
  statement->param_list_->Accept(this);
}

void SymbolTreeVisitor::Visit(ReturnStatement* return_statement) {
  return_statement->return_expression_->Accept(this);
}

void SymbolTreeVisitor::Visit(Program* program) {
  if (program == nullptr) {
    throw std::runtime_error("Syntax error");
  }
  program->main_class_->Accept(this);
  program->class_declarations_->Accept(this);
//    program->expression_->Accept(this); // tos value is called
}

void SymbolTreeVisitor::Visit(MainClass* main_class) {
  this_ = main_class->identifier;

  ParamList* empty_param_list = new ParamList();
  Function* main_function = new Function("void", "main", empty_param_list, main_class->statements_);
  current_layer_->DeclareFunction(Symbol(main_function->name_), main_function);

  auto new_layer = new ScopeLayer(current_layer_);

  current_layer_ = new_layer;

  main_function->param_list_->Accept(this);
  main_function->statements_->Accept(this);

  tree_.AddMapping(Symbol(main_function->name_), new_layer);

  current_layer_ = current_layer_->GetParent();

  functions_[Symbol(main_function->name_)] = main_function;
}

void SymbolTreeVisitor::Visit(ThisExpression* this_expression) {
  //// TODO in CE
}

ScopeLayerTree SymbolTreeVisitor::GetRoot() {
  return tree_;
}

std::unordered_map<Symbol, Function*> SymbolTreeVisitor::GetFunctions() const {
  return functions_;
}