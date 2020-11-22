#include "MemExpression.h"

namespace IRT {

void MemExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

MemExpression::MemExpression(Expression* expression) : expression_(expression) {}

IRT::NodeType MemExpression::GetNodeType() {
  return NodeType::MEM;
}

}  // namespace IRT