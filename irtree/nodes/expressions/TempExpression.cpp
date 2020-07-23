#include "TempExpression.h"

void IRT::TempExpression::Accept(IRT::Visitor* visitor) {
  visitor->Visit(this);
}

IRT::TempExpression::TempExpression(const IRT::Temporary& temporary) : temporary_(temporary) {}

IRT::NodeType IRT::TempExpression::GetNodeType() {
  return IRT::NodeType::TEMP;
}
