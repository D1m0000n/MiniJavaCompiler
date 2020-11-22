#pragma once
#include <BinaryExpression.h>

class SubtractExpression : public BinaryExpression {
 public:
  SubtractExpression(Expression* e1, Expression* e2);
  void Accept(Visitor* visitor) override;
};