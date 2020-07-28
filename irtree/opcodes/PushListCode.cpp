#include "PushListCode.h"

void IRT::PushListCode::Accept(IRT::OpCodeVisitor* visitor) {
  visitor->Visit(this);
}

void IRT::PushListCode::SetSuffix(std::string suffix) {
  suffix_ = suffix;
}

IRT::PushListCode::PushListCode(std::vector<int> registers) : registers_(registers){
  operation_ = "push";
}
