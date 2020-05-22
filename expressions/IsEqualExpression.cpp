#include <IsEqualExpression.h>

IsEqualExpression::IsEqualExpression(Expression* e1, Expression* e2) : BinaryExpression(e1, e2) {}

int IsEqualExpression::eval() const {
  return first->eval() == second->eval();
}

void IsEqualExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}