#include "AddExpression.h"

AddExpression::AddExpression(Expression *e1, Expression *e2): BinaryExpression(e1, e2) {}

int AddExpression::eval() const {
    return first->eval() + second->eval();
}

void AddExpression::Accept(Visitor* visitor) {
    visitor->Visit(this);
}