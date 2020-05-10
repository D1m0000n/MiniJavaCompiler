#include <IsGreaterExpression.h>

IsGreaterExpression::IsGreaterExpression(Expression* e1, Expression* e2) : first(e1), second(e2) {}

int IsGreaterExpression::eval() const {
  return first->eval() > second->eval();
}

void IsGreaterExpression::AcceptVisitor(Visitor* visitor) {
  visitor->Visit(this);
}