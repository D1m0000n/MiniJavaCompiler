#include <NumberExpression.h>

NumberExpression::NumberExpression(int value) {
  value_ = value;
}

int NumberExpression::eval() const {
  return value_;
}

void NumberExpression::AcceptVisitor(Visitor* visitor) {
  visitor->Visit(this);
}