#include "PopCode.h"

IRT::PopCode::PopCode(std::string reg, OpType reg_tp) : reg_(reg), reg_type_(reg_tp) {
  operation_ = "pop";
}

void IRT::PopCode::SetSuffix(std::string suffix) {
  suffix_ = suffix;
}

void IRT::PopCode::Accept(IRT::OpCodeVisitor* visitor) {
  visitor->Visit(this);
}
