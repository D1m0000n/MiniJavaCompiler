#pragma once

#include "OpCode.h"

namespace IRT {
class StrCode : public OpCode {
 public:
  StrCode(
      std::string regs,
      OpType regs_tp,
      std::string regaddr,
      OpType regaddr_tp,
      int offset
  );
  void Accept(OpCodeVisitor* visitor) override;
  void SetSuffix(std::string suffix) override;

  std::string regs_;
  OpType regs_type_;
  std::string regaddr_;
  OpType regaddr_type_;

  int offset_;

};
}
