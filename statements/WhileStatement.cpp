#include "WhileStatement.h"

WhileStatement::WhileStatement(
    Expression* expression,
    ScopeAssignmentList* statement
) : expression_(expression), statement_(statement) {}

void WhileStatement::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
