#include "PopListCode.h"

void IRT::PopListCode::Accept(IRT::OpCodeVisitor* visitor) {
  visitor->Visit(this);
}

void IRT::PopListCode::SetSuffix(std::string suffix) {
  suffix_ = suffix;
}

IRT::PopListCode::PopListCode(std::vector<int> registers) : registers_(registers) {
  operation_ = "pop";
}
