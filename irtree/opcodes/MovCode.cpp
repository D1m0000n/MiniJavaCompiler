#include "MovCode.h"

IRT::MovCode::MovCode(
    std::string regd,
    OpType reg_tp,
    std::string arg,
    OpType arg_tp
    ) : regd_(regd), regd_type_(reg_tp), arg_(arg), arg_type_(arg_tp) {
  operation_ = "mov";
}

void IRT::MovCode::SetSuffix(std::string suffix) {
  suffix_ = suffix;
}

void IRT::MovCode::Accept(IRT::OpCodeVisitor* visitor) {
  visitor->Visit(this);
}
