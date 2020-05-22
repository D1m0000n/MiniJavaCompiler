#include <ModuloExpression.h>

ModuloExpression::ModuloExpression(Expression* e1, Expression* e2) : BinaryExpression(e1, e2) {}

int ModuloExpression::eval() const {
  return first->eval() % second->eval();
}

void ModuloExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}