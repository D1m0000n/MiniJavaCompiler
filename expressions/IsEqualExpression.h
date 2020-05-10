#pragma once
#include <Expression.h>

class IsEqualExpression : public Expression {
 public:
  IsEqualExpression(Expression* e1, Expression* e2);
  [[nodiscard]] int eval() const override;
  void AcceptVisitor(Visitor* visitor) override;
  Expression* first;
  Expression* second;
};