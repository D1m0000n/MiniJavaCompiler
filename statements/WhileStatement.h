#pragma once

#include "expressions/Expression.h"
#include "Statement.h"
#include "ScopeAssignmentList.h"

class WhileStatement : public Statement {
 public:
  explicit WhileStatement(Expression* expression, ScopeAssignmentList* statement);
  void Accept(Visitor* visitor) override;

  Expression* expression_;
  ScopeAssignmentList* statement_;
};

