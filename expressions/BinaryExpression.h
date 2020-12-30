#pragma once

#include <Expression.h>

class BinaryExpression : public Expression {
 public:
  BinaryExpression(Expression* first, Expression* second) : first(first), second(second) {}

  Expression* first;
  Expression* second;
};