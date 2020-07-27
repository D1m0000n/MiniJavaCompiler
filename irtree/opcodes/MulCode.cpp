#include "MulCode.h"

IRT::MulCode::MulCode(
    std::string regd,
    OpType regd_tp,
    std::string rega,
    OpType rega_tp,
    std::string argb,
    OpType argb_tp
) : regd_(regd), regd_type_(regd_tp), rega_(rega), rega_type_(rega_tp), argb_(argb), argb_type_(argb_tp) {
  operation_ = "mul";
  suffix_ = "";
}

void IRT::MulCode::SetSuffix(std::string suffix) {
  suffix_ = suffix;
}

void IRT::MulCode::Accept(IRT::OpCodeVisitor* visitor) {
  visitor->Visit(this);
}
