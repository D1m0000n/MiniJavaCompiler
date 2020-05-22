#pragma once
#include <BinaryExpression.h>

class IsGreaterExpression : public BinaryExpression {
 public:
  IsGreaterExpression(Expression* e1, Expression* e2);
  [[nodiscard]] int eval() const override;
  void Accept(Visitor* visitor) override;
};