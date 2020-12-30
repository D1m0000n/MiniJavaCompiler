#include "IfStatement.h"

IfStatement::IfStatement(
    Expression* expression,
    ScopeAssignmentList* if_statement,
    ScopeAssignmentList* else_statement
) : expression_(expression), true_statement_(if_statement), false_statement_(else_statement) {}

void IfStatement::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
