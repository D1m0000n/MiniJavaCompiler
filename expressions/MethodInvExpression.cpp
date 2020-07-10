#include "MethodInvExpression.h"

#include <utility>

MethodInvExpression::MethodInvExpression(
    Expression* expr, const std::string& identifier,
    std::vector<Expression*> expr_list)
    : expr(std::move(expr)), identifier_(identifier), expr_list(std::move(expr_list)) {}

int MethodInvExpression::eval() const {
}

void MethodInvExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}