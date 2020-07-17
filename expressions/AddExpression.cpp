#include "AddExpression.h"

AddExpression::AddExpression(Expression *e1, Expression *e2): BinaryExpression(e1, e2) {}

void AddExpression::Accept(Visitor* visitor) {
    visitor->Visit(this);
}