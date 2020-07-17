#pragma once
#include <BinaryExpression.h>

class ModuloExpression : public BinaryExpression {
 public:
  ModuloExpression(Expression* e1, Expression* e2);
  void Accept(Visitor* visitor) override;
};