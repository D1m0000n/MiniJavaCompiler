#pragma once
#include <BinaryExpression.h>

class OrExpression : public BinaryExpression {
 public:
  OrExpression(Expression* e1, Expression* e2);
  [[nodiscard]] int eval() const override;
  void Accept(Visitor* visitor) override;
};