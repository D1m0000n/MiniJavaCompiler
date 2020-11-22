#pragma once

#include "expressions/Expression.h"
#include "Statement.h"

#include <string>

class Assignment : public Statement {
 public:
  Assignment(std::string variable, Expression* expression);
  void Accept(Visitor* visitor) override;

  std::string variable_;
  Expression* expression_;
};