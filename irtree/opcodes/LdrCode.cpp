#include "LdrCode.h"

IRT::LdrCode::LdrCode(
    std::string regd,
    IRT::OpType regd_tp,
    std::string regaddr,
    IRT::OpType regaddr_tp,
    int offset
) : regd_(regd), regd_type_(regd_tp), regaddr_(regaddr), regaddr_type_(regaddr_tp), offset_(offset) {
  operation_ = "ldr";
}

void IRT::LdrCode::SetSuffix(std::string suffix) {
  suffix_ = suffix;
}

void IRT::LdrCode::Accept(IRT::OpCodeVisitor* visitor) {
  visitor->Visit(this);
}
