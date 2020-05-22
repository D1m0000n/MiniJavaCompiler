#pragma once
#include <BinaryExpression.h>

class ModuloExpression : public BinaryExpression {
 public:
  ModuloExpression(Expression* e1, Expression* e2);
  [[nodiscard]] int eval() const override;
  void Accept(Visitor* visitor) override;
};