#pragma once
#include <BinaryExpression.h>

class OrExpression : public BinaryExpression {
 public:
  OrExpression(Expression* e1, Expression* e2);
  void Accept(Visitor* visitor) override;
};