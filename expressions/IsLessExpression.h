#pragma once
#include <BinaryExpression.h>

class IsLessExpression : public BinaryExpression {
 public:
  IsLessExpression(Expression* e1, Expression* e2);
  void Accept(Visitor* visitor) override;
};