#include "PrintStatement.h"

IRT::PrintStatement::PrintStatement(Expression *expression) : expression_(expression) {}

void IRT::PrintStatement::Accept(IRT::Visitor* visitor) {
  visitor->Visit(this);
}

IRT::NodeType IRT::PrintStatement::GetNodeType() {
  return IRT::NodeType::PRINT;
}
