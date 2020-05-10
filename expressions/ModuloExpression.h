#pragma once
#include <Expression.h>

class ModuloExpression : public Expression {
 public:
  ModuloExpression(Expression* e1, Expression* e2);
  [[nodiscard]] int eval() const override;
  void AcceptVisitor(Visitor* visitor) override;
  Expression* first;
  Expression* second;
};