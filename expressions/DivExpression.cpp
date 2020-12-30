#include "DivExpression.h"

DivExpression::DivExpression(
    Expression* e1, Expression* e2
) : BinaryExpression(e1, e2) {}

void DivExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}