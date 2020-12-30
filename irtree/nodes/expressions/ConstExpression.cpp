#include "ConstExpression.h"

void IRT::ConstExpression::Accept(IRT::Visitor* visitor) {
  visitor->Visit(this);
}

IRT::ConstExpression::ConstExpression(int value) : value_(value) {}

int IRT::ConstExpression::Value() const {
  return value_;
}

IRT::NodeType IRT::ConstExpression::GetNodeType() {
  return IRT::NodeType::CONST;
}
