#include <ModuloExpression.h>

ModuloExpression::ModuloExpression(Expression* e1, Expression* e2) : BinaryExpression(e1, e2) {}

void ModuloExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}