#include "DivCode.h"

IRT::DivCode::DivCode(
    std::string regd,
    OpType regd_tp,
    std::string rega,
    OpType rega_tp,
    std::string argb,
    OpType argb_tp
) : regd_(regd), regd_type_(regd_tp), rega_(rega), rega_type_(rega_tp), argb_(argb), argb_type_(argb_tp) {
  operation_ = "sdiv";
}

void IRT::DivCode::SetSuffix(std::string suffix) {
  suffix_ = suffix;
}

void IRT::DivCode::Accept(IRT::OpCodeVisitor* visitor) {
  visitor->Visit(this);
}
