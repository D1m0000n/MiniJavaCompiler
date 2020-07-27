#include "StrCode.h"

IRT::StrCode::StrCode(
    std::string regs,
    IRT::OpType regs_tp,
    std::string regaddr,
    IRT::OpType regaddr_tp,
    int offset
) : regs_(regs), regs_type_(regs_tp), regaddr_(regaddr), regaddr_type_(regaddr_tp), offset_(offset) {
  operation_ = "str";
}

void IRT::StrCode::SetSuffix(std::string suffix) {
  suffix_ = suffix;
}

void IRT::StrCode::Accept(IRT::OpCodeVisitor* visitor) {
  visitor->Visit(this);
}
