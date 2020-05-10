#include <IsEqualExpression.h>

IsEqualExpression::IsEqualExpression(Expression* e1, Expression* e2) : first(e1), second(e2) {}

int IsEqualExpression::eval() const {
  return first->eval() == second->eval();
}

void IsEqualExpression::AcceptVisitor(Visitor* visitor) {
  visitor->Visit(this);
}