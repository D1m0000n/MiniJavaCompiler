#include "LabelStatement.h"

namespace IRT {

void LabelStatement::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

LabelStatement::LabelStatement(IRT::Label label) : label_(label) {}

IRT::NodeType LabelStatement::GetNodeType() {
  return NodeType::LABEL;
}
}