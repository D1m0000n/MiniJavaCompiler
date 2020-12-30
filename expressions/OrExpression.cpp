#include <OrExpression.h>

OrExpression::OrExpression(Expression* e1, Expression* e2) : BinaryExpression(e1, e2) {}

void OrExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}