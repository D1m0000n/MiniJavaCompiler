#include "MethodInvExpression.h"

#include <utility>

MethodInvExpression::MethodInvExpression(
    Expression* expression, std::string identifier,
    std::vector<Expression*> expression_list)
    : expression_(expression), identifier_(std::move(identifier)), expression_list_(std::move(expression_list)) {}

int MethodInvExpression::eval() const {
}

void MethodInvExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}