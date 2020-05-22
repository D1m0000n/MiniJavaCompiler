#include <IsGreaterExpression.h>

IsGreaterExpression::IsGreaterExpression(Expression* e1, Expression* e2) : BinaryExpression(e1, e2) {}

int IsGreaterExpression::eval() const {
  return first->eval() > second->eval();
}

void IsGreaterExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}