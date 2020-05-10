#pragma once
#include <Expression.h>

class NumberExpression : public Expression {
 public:
  explicit NumberExpression(int value);
  [[nodiscard]] int eval() const override;
  void AcceptVisitor(Visitor* visit) override;

  int value_;
};