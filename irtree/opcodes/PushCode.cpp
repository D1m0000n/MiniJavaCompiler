#include "PushCode.h"

IRT::PushCode::PushCode(std::string reg, OpType reg_tp) : reg_(reg), reg_type_(reg_tp) {
  operation_ = "pop";
}

void IRT::PushCode::SetSuffix(std::string suffix) {
  suffix_ = suffix;
}

void IRT::PushCode::Accept(IRT::OpCodeVisitor* visitor) {
  visitor->Visit(this);
}
