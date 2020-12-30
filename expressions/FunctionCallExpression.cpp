#include "FunctionCallExpression.h"

#include <utility>

FunctionCallExpression::FunctionCallExpression(Expression* expression, std::string name, ParamValueList* param_list) :
    expression_(expression),
    param_list_(param_list),
    name_(std::move(name)) {
}

void FunctionCallExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
