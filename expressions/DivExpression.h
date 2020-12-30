#pragma once
#include <BinaryExpression.h>

class DivExpression : public BinaryExpression {
 public:
  DivExpression(Expression* e1, Expression* e2);
  void Accept(Visitor* visitor) override;
};