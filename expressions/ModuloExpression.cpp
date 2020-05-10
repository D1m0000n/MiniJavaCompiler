#include <ModuloExpression.h>

ModuloExpression::ModuloExpression(Expression* e1, Expression* e2) : first(e1), second(e2) {}

int ModuloExpression::eval() const {
  return first->eval() % second->eval();
}

void ModuloExpression::AcceptVisitor(Visitor* visitor) {
  visitor->Visit(this);
}