#include "AndExpression.h"

AndExpression::AndExpression(Expression* e1, Expression* e2) : BinaryExpression(e1, e2) {}

void AndExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}