#include "Interpreter.h"

#include "elements.h"

#include <iostream>

#include "objects/Integer.h"

Interpreter::Interpreter(ScopeLayerTree root) : tree_(root) {

  current_layer_ = tree_.root_;
  offsets_.push(0);
  tos_value_ = 0;
}

void Interpreter::Visit(NumberExpression* expression) {
  tos_value_ = expression->value_;
}

void Interpreter::Visit(AddExpression* expression) {
  tos_value_ = Accept(expression->first) + Accept(expression->second);
}

void Interpreter::Visit(SubtractExpression* expression) {
  tos_value_ = Accept(expression->first) - Accept(expression->second);
}

void Interpreter::Visit(MulExpression* expression) {
  tos_value_ = Accept(expression->first) * Accept(expression->second);
}

void Interpreter::Visit(DivExpression* expression) {
  tos_value_ = Accept(expression->first) / Accept(expression->second);
}

void Interpreter::Visit(AndExpression* expression) {
  tos_value_ = Accept(expression->first) && Accept(expression->second);
}

void Interpreter::Visit(IsEqualExpression* expression) {
  tos_value_ = Accept(expression->first) == Accept(expression->second);
}

void Interpreter::Visit(IsGreaterExpression* expression) {
  tos_value_ = Accept(expression->first) > Accept(expression->second);
}

void Interpreter::Visit(IsLessExpression* expression) {
  tos_value_ = Accept(expression->first) < Accept(expression->second);
}

void Interpreter::Visit(ModuloExpression* expression) {
  tos_value_ = Accept(expression->first) % Accept(expression->second);
}

void Interpreter::Visit(OrExpression* expression) {
  tos_value_ = Accept(expression->first) || Accept(expression->second);
}

void Interpreter::Visit(IdentExpression* expression) {
  try {
    tos_value_ = current_layer_->Get(Symbol(expression->ident_))->ToInt();
  } catch (std::runtime_error& error) {
    std::cout << error.what() << std::endl;
    exit(1);
  }
}

void Interpreter::Visit(Assignment* assignment) {
  int value = Accept(assignment->expression_);

  current_layer_->Put(Symbol(assignment->variable_), std::make_shared<Integer>(value));
}

void Interpreter::Visit(PrintStatement* statement) {
  int value = Accept(statement->expression_);

  std::cout << value << std::endl;
}

void Interpreter::Visit(AssignmentList* assignment_list) {
  for (Statement* assignment: assignment_list->statements_) {
    assignment->Accept(this);
  }
}

void Interpreter::Visit(VarDecl* var_decl) {
  std::cout << "Var decl called: " << var_decl->variable_ << std::endl;
}

void Interpreter::Visit(DeclarationList* declaration_list) {
  for (Declaration* declaration : declaration_list->declarations_) {
    declaration->Accept(this);
  }
}

void Interpreter::Visit(ClassDecl* class_decl) {
}

void Interpreter::Visit(MethodDecl* method_decl) {
}

void Interpreter::Visit(ScopeAssignmentList* list) {
  std::cout << "Going inside" << std::endl;

  current_layer_ = current_layer_->GetChild(offsets_.top());

  offsets_.push(0);
  list->statement_list->Accept(this);

  offsets_.pop();
  size_t index = offsets_.top();

  offsets_.pop();
  offsets_.push(index + 1);

  current_layer_ = current_layer_->GetParent();
}

void Interpreter::Visit(IfStatement* if_statement) {
  if_statement->expression_->Accept(this);
  if (tos_value_) {
    std::cout << "Chosen true branch" << std::endl;
    if_statement->true_statement_->Accept(this);
  } else {
    size_t index = offsets_.top();
    offsets_.pop();
    offsets_.push(index + 1);
    std::cout << "Chosen false  branch" << std::endl;
    if_statement->false_statement_->Accept(this);
  }
}

void Interpreter::Visit(WhileStatement* while_statement) {
  while_statement->expression_->Accept(this);
  while (tos_value_) {
    while_statement->statement_->Accept(this);
    size_t index = offsets_.top();
    offsets_.pop();
    offsets_.push(index - 1);
    while_statement->expression_->Accept(this);
  }
}

void Interpreter::Visit(Program* program) {
  program->main_class_->Accept(this);
}

void Interpreter::Visit(MainClass* main_class) {
  main_class->statements_->Accept(this);
}

void Interpreter::GetResult(Program* program) {
  Visit(program);
}

void Interpreter::Visit(Function* function) {}

void Interpreter::Visit(ParamList* param_list) {}

void Interpreter::Visit(FunctionList* function_list) {}

void Interpreter::Visit(ParamValueList* param_value_list) {}

void Interpreter::Visit(FunctionCallExpression* statement) {}

void Interpreter::Visit(ReturnStatement* statement) {}

void Interpreter::Visit(ThisExpression* this_expression) {}