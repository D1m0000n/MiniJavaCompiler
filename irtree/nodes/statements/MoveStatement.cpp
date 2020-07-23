#include "MoveStatement.h"

namespace IRT {
void MoveStatement::Accept(IRT::Visitor* visitor) {
  visitor->Visit(this);
}
MoveStatement::MoveStatement(
    Expression* source,
    Expression* target
) : source_(source), target_(target) {}

IRT::NodeType MoveStatement::GetNodeType() {
  return NodeType::MOVE;
}

}
