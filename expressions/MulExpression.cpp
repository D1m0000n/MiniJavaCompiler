#include "MulExpression.h"

MulExpression::MulExpression(
    Expression *e1, Expression *e2
): BinaryExpression(e1, e2) {}

int MulExpression::eval() const {
    return first->eval() * second->eval();
}

void MulExpression::Accept(Visitor* visitor) {
    visitor->Visit(this);
}