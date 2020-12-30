#include <IsLessExpression.h>

IsLessExpression::IsLessExpression(Expression* e1, Expression* e2) : BinaryExpression(e1, e2) {}

void IsLessExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}