#include <objects/Integer.h>
#include <iostream>
#include <function-mechanisms/FunctionStorage.h>
#include "FunctionCallVisitor.h"

#include "elements.h"

void FunctionCallVisitor::Visit(NumberExpression* expression) {
  tos_value_ = expression->value_;
}

void FunctionCallVisitor::Visit(AddExpression* expression) {
  tos_value_ = Accept(expression->first) + Accept(expression->second);
}

void FunctionCallVisitor::Visit(SubtractExpression* expression) {
  tos_value_ = Accept(expression->first) - Accept(expression->second);
}

void FunctionCallVisitor::Visit(MulExpression* expression) {
  tos_value_ = Accept(expression->first) * Accept(expression->second);
}

void FunctionCallVisitor::Visit(DivExpression* expression) {
  tos_value_ = Accept(expression->first) / Accept(expression->second);
}

void FunctionCallVisitor::Visit(AndExpression* expression) {
  tos_value_ = (Accept(expression->first) && Accept(expression->second));
}

void FunctionCallVisitor::Visit(IsEqualExpression* expression) {
  tos_value_ = (Accept(expression->first) == Accept(expression->second));
}

void FunctionCallVisitor::Visit(IsGreaterExpression* expression) {
  tos_value_ = (Accept(expression->first) > Accept(expression->second));
}

void FunctionCallVisitor::Visit(IsLessExpression* expression) {
  tos_value_ = (Accept(expression->first) < Accept(expression->second));
}

void FunctionCallVisitor::Visit(ModuloExpression* expression) {
  int module = Accept(expression->second);
  if (!module) {
    throw std::runtime_error("Modulo by zero");
  }
  tos_value_ = (Accept(expression->first) % module);
}

void FunctionCallVisitor::Visit(OrExpression* expression) {
  tos_value_ = (Accept(expression->first) || Accept(expression->second));
}

void FunctionCallVisitor::Visit(IdentExpression* expression) {
  int index = table_.Get(Symbol(expression->ident_));
  tos_value_ = frame.Get(index);
}

void FunctionCallVisitor::Visit(Assignment* assignment) {
  int value = Accept(assignment->expression_);

  int index = table_.Get(Symbol(assignment->variable_));
  frame.Set(index, value);
}

void FunctionCallVisitor::Visit(VarDecl* var_decl) {
  size_t index = frame.AllocVariable();
  table_.CreateVariable(Symbol(var_decl->variable_));
  table_.Put(Symbol(var_decl->variable_), index);

}

void FunctionCallVisitor::Visit(PrintStatement* statement) {
  int value = Accept(statement->expression_);

  std::cout << value << std::endl;
}

void FunctionCallVisitor::Visit(AssignmentList* assignment_list) {
  for (Statement* assignment: assignment_list->statements_) {
    std::string saved_this = this_;
    if (!returned_) {
      assignment->Accept(this);
    }
    this_ = saved_this;
  }
}

void FunctionCallVisitor::Visit(ScopeAssignmentList* list) {
  std::cout << "Going inside" << std::endl;

  current_layer_ = current_layer_->GetChild(offsets_.top());

  offsets_.push(0);
  frame.AllocScope();
  table_.BeginScope();
  list->statement_list->Accept(this);

  offsets_.pop();
  size_t index = offsets_.top();

  offsets_.pop();
  offsets_.push(index + 1);

  current_layer_ = current_layer_->GetParent();
  frame.DeallocScope();
  table_.EndScope();
}

void FunctionCallVisitor::Visit(Program* program) {

}

void FunctionCallVisitor::Visit(ParamList* param_list) {
  int index = -1;
  for (auto param: param_list->params_) {
    table_.CreateVariable(Symbol(param));
    table_.Put(Symbol(param), index);
    --index;
  }
}

void FunctionCallVisitor::Visit(Function* function) {
  function->param_list_->Accept(this);
  function->statements_->Accept(this);
}

FunctionCallVisitor::FunctionCallVisitor(
    ScopeLayer* function_scope, std::shared_ptr<Method> function
) : root_layer(function_scope), frame(function) {
  current_layer_ = root_layer;
  offsets_.push(0);
  tos_value_ = 0;
}

void FunctionCallVisitor::SetParams(const std::vector<int>& params) {
  frame.SetParams(params);
}

void FunctionCallVisitor::Visit(FunctionCallExpression* statement) {
  std::cerr << "Function called " << statement->name_ << std::endl;
  std::string full_func_name;
  IdentExpression* ident_expression = dynamic_cast<IdentExpression*>(statement->expression_);
  if (ident_expression->ident_ == "this") {
    full_func_name = this_ + "." + statement->name_;
  } else {
    this_ = ident_expression->ident_;
    full_func_name = ident_expression->ident_ + "." + statement->name_;
  }
  auto function_type = current_layer_->Get(full_func_name);

  std::shared_ptr<Method> func_converted = std::dynamic_pointer_cast<Method>(function_type);

  if (func_converted == nullptr) {
    throw std::runtime_error("Function not defined");
  }

  std::vector<int> params;

  for (auto param : statement->param_list_->params_) {
    params.push_back(Accept(param));
  }

  FunctionCallVisitor new_visitor(
      tree_->GetFunctionScopeByName(full_func_name),
      func_converted
  );
  new_visitor.SetParams(params);
  new_visitor.SetTree(tree_);
  new_visitor.SetThis(this_);
  new_visitor.GetFrame().SetParentFrame(&frame);
  new_visitor.Visit(FunctionStorage::GetInstance().Get(Symbol(full_func_name)));

  tos_value_ = frame.GetReturnValue();
}

void FunctionCallVisitor::Visit(FunctionList* function_list) {

}

void FunctionCallVisitor::Visit(ParamValueList* value_list) {

}

void FunctionCallVisitor::Visit(ReturnStatement* return_statement) {
  if (frame.HasParent()) {
    frame.SetParentReturnValue(Accept(return_statement->return_expression_));
  }
  returned_ = true;
}

void FunctionCallVisitor::Visit(IfStatement* if_statement) {

  int expression_result = Accept(if_statement->expression_);
  if (expression_result == 1) {
    current_layer_ = current_layer_->GetChild(offsets_.top());
    offsets_.push(0);
    frame.AllocScope();
    table_.BeginScope();
    ScopeAssignmentList* assignment_list = dynamic_cast<ScopeAssignmentList*>(if_statement->true_statement_);
//    if_statement->true_statement_->Accept(this);
    assignment_list->statement_list->Accept(this);
    offsets_.pop();
    size_t index = offsets_.top();
    offsets_.pop();
    offsets_.push(index + 2); // skip else child
    current_layer_ = current_layer_->GetParent();
    frame.DeallocScope();
    table_.EndScope();
  } else {
    int value = offsets_.top();

    offsets_.push(0);

    current_layer_ = current_layer_->GetChild(value + 1); // else layer
    frame.AllocScope();
    table_.BeginScope();
    if (if_statement->false_statement_) {
      ScopeAssignmentList* assignment_list = dynamic_cast<ScopeAssignmentList*>(if_statement->false_statement_);
//      if_statement->false_statement_->Accept(this);
      assignment_list->statement_list->Accept(this);
    }
    offsets_.pop();
    offsets_.pop();
    offsets_.push(value + 2);

    current_layer_ = current_layer_->GetParent();
    frame.DeallocScope();
    table_.EndScope();
  }
}

void FunctionCallVisitor::Visit(WhileStatement* while_statement) {
  int expression_result = Accept(while_statement->expression_);
  while (expression_result) {
    current_layer_ = current_layer_->GetChild(offsets_.top());
    offsets_.push(0);
    frame.AllocScope();
    table_.BeginScope();
    ScopeAssignmentList* assignment_list = dynamic_cast<ScopeAssignmentList*>(while_statement->statement_);
    assignment_list->statement_list->Accept(this);
//    while_statement->statement_->Accept(this);
    offsets_.pop();
    size_t index = offsets_.top();
    offsets_.pop();
    offsets_.push(index + 1);

    frame.DeallocScope();
    table_.EndScope();

    expression_result = Accept(while_statement->expression_);
  }
}

void FunctionCallVisitor::Visit(DeclarationList* declaration_list) {
  for (auto declaration : declaration_list->declarations_) {
    declaration->Accept(this);
  }
}

void FunctionCallVisitor::Visit(ClassDecl* class_decl) {
  SetThis(class_decl->identifier);
  class_decl->declaration_list_->Accept(this);
}

void FunctionCallVisitor::Visit(MethodDecl* method_decl) {
  method_decl->assignment_list_->Accept(this);
}

void FunctionCallVisitor::Visit(MainClass* main_class) {
  main_class->statements_->Accept(this);
}

void FunctionCallVisitor::Visit(ThisExpression* this_expression) {
}

void FunctionCallVisitor::SetTree(ScopeLayerTree* tree) {
  tree_ = tree;
}

FrameEmulator& FunctionCallVisitor::GetFrame() {
  return frame;
}

void FunctionCallVisitor::SetThis(std::string identifier) {
  this_ = identifier;
}
