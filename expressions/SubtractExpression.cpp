#include "SubtractExpression.h"

SubtractExpression::SubtractExpression(Expression *e1, Expression *e2): first(e1), second(e2) {}

int SubtractExpression::eval() const {
    return first->eval() - second->eval();
}

void SubtractExpression::Accept(Visitor *visitor) {
    visitor->Visit(this);
}