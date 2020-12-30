#include "BinopExpression.h"

void IRT::BinopExpression::Accept(IRT::Visitor* visitor) {
  visitor->Visit(this);

}
IRT::BinopExpression::BinopExpression(
    IRT::BinaryOperatorType type,
    IRT::Expression* first,
    IRT::Expression* second
) : operator_type_(type), first_(first), second_(second) {}

IRT::NodeType IRT::BinopExpression::GetNodeType() {
  return IRT::NodeType::BINOP;
}
