#pragma once
#include <BinaryExpression.h>

class MulExpression: public BinaryExpression {
 public:
    MulExpression(Expression* e1, Expression* e2);
    int eval() const override;
    void Accept(Visitor* visitor) override;
};