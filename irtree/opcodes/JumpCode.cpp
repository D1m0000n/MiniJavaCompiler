#include "JumpCode.h"

IRT::JumpCode::JumpCode(std::string label) : label_(label) {
  operation_ = "b";
}

void IRT::JumpCode::SetSuffix(std::string suffix) {
  suffix_ = suffix;
}

void IRT::JumpCode::Accept(IRT::OpCodeVisitor* visitor) {
  visitor->Visit(this);
}
