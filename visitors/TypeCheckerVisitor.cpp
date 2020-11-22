#include "TypeCheckerVisitor.h"
#include <FunctionStorage.h>

#include "elements.h"

#include <iostream>

#include "objects/Integer.h"

TypeCheckerVisitor::TypeCheckerVisitor(ScopeLayerTree* root) : tree_(root) {
  offsets_.push(0);
  tos_value_ = "";
}

void TypeCheckerVisitor::Visit(NumberExpression* expression) {
  tos_value_ = "int";
}

void TypeCheckerVisitor::Visit(AddExpression* expression) {
  BinaryTypesCheck(expression, "AddExpression");
}

void TypeCheckerVisitor::Visit(SubtractExpression* expression) {
  BinaryTypesCheck(expression, "SubtractExpression");
}

void TypeCheckerVisitor::Visit(MulExpression* expression) {
  BinaryTypesCheck(expression, "MulExpression");
}

void TypeCheckerVisitor::Visit(DivExpression* expression) {
  BinaryTypesCheck(expression, "DivExpression");
}

void TypeCheckerVisitor::Visit(AndExpression* expression) {
  BinaryTypesCheck(expression, "AndExpression");
}

void TypeCheckerVisitor::Visit(IsEqualExpression* expression) {
  BinaryTypesCheck(expression, "IsEqualExpression");
}

void TypeCheckerVisitor::Visit(IsGreaterExpression* expression) {
  BinaryTypesCheck(expression, "IsGreaterExpression");
}

void TypeCheckerVisitor::Visit(IsLessExpression* expression) {
  BinaryTypesCheck(expression, "IsLessExpression");
}

void TypeCheckerVisitor::Visit(ModuloExpression* expression) {
  BinaryTypesCheck(expression, "ModuloExpression");
}

void TypeCheckerVisitor::Visit(OrExpression* expression) {
  BinaryTypesCheck(expression, "OrExpression");
}

void TypeCheckerVisitor::Visit(IdentExpression* expression) {
  auto identifier = current_layer_->Get(expression->ident_);
  tos_value_ = identifier->Type();
}

void TypeCheckerVisitor::Visit(Assignment* assignment) {
  auto identifier = current_layer_->Get(assignment->variable_);
  std::string left_side_type = identifier->Type();
  std::string right_side_type = Accept(assignment->expression_);
  if (left_side_type != right_side_type) {
    throw std::runtime_error("Different operands is Assignment");
  }
}

void TypeCheckerVisitor::Visit(PrintStatement* statement) {
  Accept(statement->expression_);
}

void TypeCheckerVisitor::Visit(AssignmentList* assignment_list) {
  for (Statement* assignment: assignment_list->statements_) {
    Accept(assignment);
  }
}

void TypeCheckerVisitor::Visit(VarDecl* var_decl) {}

void TypeCheckerVisitor::Visit(DeclarationList* declaration_list) {
  for (auto declaration : declaration_list->declarations_) {
    declaration->Accept(this);
  }
}

void TypeCheckerVisitor::Visit(ClassDecl* class_decl) {
  this_ = class_decl->identifier;
  class_decl->declaration_list_->Accept(this);
}

void TypeCheckerVisitor::Visit(MethodDecl* method_decl) {
  method_decl->assignment_list_->Accept(this);
}

void TypeCheckerVisitor::Visit(ScopeAssignmentList* list) {
  current_layer_ = current_layer_->GetChild(offsets_.top());

  offsets_.push(0);
  Accept(list->statement_list);
  offsets_.pop();
  size_t index = offsets_.top();
  offsets_.pop();
  offsets_.push(index + 1);
  current_layer_ = current_layer_->GetParent();
}

void TypeCheckerVisitor::Visit(IfStatement* if_statement) {
  Accept(if_statement->true_statement_);
  if (if_statement->false_statement_) {
    Accept(if_statement->false_statement_);
  }
}

void TypeCheckerVisitor::Visit(WhileStatement* while_statement) {
  Accept(while_statement->statement_);
}

void TypeCheckerVisitor::Visit(Program* program) {
  Accept(program->main_class_);
  Accept(program->class_declarations_);
}

void TypeCheckerVisitor::Visit(MainClass* main_class) {
  this_ = main_class->identifier;
  std::string full_func_name = main_class->identifier + "." + "main";
  current_layer_ = tree_->GetFunctionScopeByName(full_func_name);
  Accept(main_class->statements_);
}

void TypeCheckerVisitor::CheckTypes(Program* program) {
  Visit(program);
}

void TypeCheckerVisitor::BinaryTypesCheck(BinaryExpression* expression, const std::string& name) {
  std::string first_type = Accept(expression->first);
  std::string second_type = Accept(expression->second);
  if (first_type != second_type) {
    std::string error_message = "Different operands in " + name;
    throw std::runtime_error(error_message);
  }
}

void TypeCheckerVisitor::Visit(Function* function) {
  std::string full_func_name = this_ + "." + function->name_;
  current_function_ = function;
  current_layer_ = tree_->GetFunctionScopeByName(full_func_name);
  Accept(function->param_list_);
  Accept(function->statements_);
}

void TypeCheckerVisitor::Visit(ParamList* param_list) {}

void TypeCheckerVisitor::Visit(ParamValueList* param_value_list) {
  for (int i = 0; i < param_value_list->params_.size(); ++i) {
    auto param = param_value_list->params_[i];
    param->Accept(this);
    if (tos_value_ != current_function_->param_list_->types_[i]) {
      throw std::runtime_error("Wrong parameter type");
    }
  }
}

void TypeCheckerVisitor::Visit(FunctionList* function_list) {
  for (auto function : function_list->functions_) {
    function->Accept(this);
  }
}

void TypeCheckerVisitor::Visit(FunctionCallExpression* statement) {}

void TypeCheckerVisitor::Visit(ReturnStatement* statement) {
  statement->return_expression_->Accept(this);
  if (current_function_->type_ == "void") {
    throw std::runtime_error("Return value from void type function");
  }
}

void TypeCheckerVisitor::Visit(ThisExpression* this_expression) {}