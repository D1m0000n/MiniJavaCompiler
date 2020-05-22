#pragma once
#include <BinaryExpression.h>

class IsLessExpression : public BinaryExpression {
 public:
  IsLessExpression(Expression* e1, Expression* e2);
  [[nodiscard]] int eval() const override;
  void Accept(Visitor* visitor) override;
};