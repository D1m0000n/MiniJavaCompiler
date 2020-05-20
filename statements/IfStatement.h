#pragma once

#include "expressions/Expression.h"
#include "Statement.h"

class IfStatement : public Statement {
 public:
  explicit IfStatement(Expression* expression, Statement* if_statement, Statement* else_statement);
  void Accept(Visitor* visitor) override;

  Expression* expression_;
  Statement* true_statement_;
  Statement* false_statement_;
};
