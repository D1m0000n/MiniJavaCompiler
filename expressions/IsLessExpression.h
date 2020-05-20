#pragma once
#include <Expression.h>

class IsLessExpression : public Expression {
 public:
  IsLessExpression(Expression* e1, Expression* e2);
  [[nodiscard]] int eval() const override;
  void Accept(Visitor* visitor) override;
  Expression* first;
  Expression* second;
};