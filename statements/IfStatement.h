#pragma once

#include "expressions/Expression.h"
#include "ScopeAssignmentList.h"
#include "Statement.h"

class IfStatement : public Statement {
 public:
  explicit IfStatement(Expression* expression, ScopeAssignmentList* if_statement, ScopeAssignmentList* else_statement);
  void Accept(Visitor* visitor) override;

  Expression* expression_;
  ScopeAssignmentList* true_statement_;
  ScopeAssignmentList* false_statement_;
};
