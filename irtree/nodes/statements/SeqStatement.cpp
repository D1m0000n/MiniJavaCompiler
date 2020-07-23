#include "SeqStatement.h"

namespace IRT {

void SeqStatement::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
SeqStatement::SeqStatement(Statement* first, Statement* second) : first_statement_(first), second_statement_(second) {}

IRT::NodeType SeqStatement::GetNodeType() {
  return NodeType::SEQ;
}
}