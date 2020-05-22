#include <IsLessExpression.h>

IsLessExpression::IsLessExpression(Expression* e1, Expression* e2) : BinaryExpression(e1, e2) {}

int IsLessExpression::eval() const {
  return first->eval() < second->eval();
}

void IsLessExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}