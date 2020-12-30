#pragma once
#include <BinaryExpression.h>

class AndExpression : public BinaryExpression {
 public:
  AndExpression(Expression* e1, Expression* e2);
  void Accept(Visitor* visitor) override;
};
