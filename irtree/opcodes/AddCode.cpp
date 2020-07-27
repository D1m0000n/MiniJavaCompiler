#include "AddCode.h"

IRT::AddCode::AddCode(
    std::string regd,
    OpType regd_tp,
    std::string rega,
    OpType rega_tp,
    std::string argb,
    OpType argb_tp
    ) : regd_(regd), regd_type_(regd_tp), rega_(rega), rega_type_(rega_tp), argb_(argb), argb_type_(argb_tp) {
  operation_ = "add";
}

void IRT::AddCode::SetSuffix(std::string suffix) {
  suffix_ = suffix;
}

void IRT::AddCode::Accept(IRT::OpCodeVisitor* visitor) {
  visitor->Visit(this);
}
