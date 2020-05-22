#pragma once
#include <BinaryExpression.h>

class IsEqualExpression : public BinaryExpression {
 public:
  IsEqualExpression(Expression* e1, Expression* e2);
  [[nodiscard]] int eval() const override;
  void Accept(Visitor* visitor) override;
};