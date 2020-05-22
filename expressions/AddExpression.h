#pragma once
#include <BinaryExpression.h>

class AddExpression: public BinaryExpression {
 public:
    AddExpression(Expression* e1, Expression* e2);
    int eval() const override;
    void Accept(Visitor* visitor) override;
};