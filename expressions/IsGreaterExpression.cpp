#include <IsGreaterExpression.h>

IsGreaterExpression::IsGreaterExpression(Expression* e1, Expression* e2) : BinaryExpression(e1, e2) {}

void IsGreaterExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}