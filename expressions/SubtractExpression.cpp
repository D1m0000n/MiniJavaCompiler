#include "SubtractExpression.h"

SubtractExpression::SubtractExpression(Expression* e1, Expression* e2) : BinaryExpression(e1, e2) {}

void SubtractExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}