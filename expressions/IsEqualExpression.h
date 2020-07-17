#pragma once
#include <BinaryExpression.h>

class IsEqualExpression : public BinaryExpression {
 public:
  IsEqualExpression(Expression* e1, Expression* e2);
  void Accept(Visitor* visitor) override;
};