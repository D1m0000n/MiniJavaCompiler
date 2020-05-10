#include <IsLessExpression.h>

IsLessExpression::IsLessExpression(Expression* e1, Expression* e2) : first(e1), second(e2) {}

int IsLessExpression::eval() const {
  return first->eval() < second->eval();
}

void IsLessExpression::AcceptVisitor(Visitor* visitor) {
  visitor->Visit(this);
}