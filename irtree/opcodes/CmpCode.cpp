#include "CmpCode.h"

IRT::CmpCode::CmpCode(
    std::string rega,
    IRT::OpType rega_tp,
    std::string argb,
    IRT::OpType argb_tp
    ) : rega_(rega), rega_type_(rega_tp), argb_(argb), argb_type_(argb_tp) {
  operation_ = "cmp";
}

void IRT::CmpCode::SetSuffix(std::string suffix) {
  suffix_ = suffix;
}

void IRT::CmpCode::Accept(IRT::OpCodeVisitor* visitor) {
  visitor->Visit(this);
}
