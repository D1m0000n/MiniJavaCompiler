#pragma once

#include "OpCode.h"

namespace IRT {
class PushCode : public OpCode {
 public:
  PushCode(std::string reg, OpType reg_tp);
  void Accept(OpCodeVisitor* visitor) override;
  void SetSuffix(std::string suffix) override;

  std::string reg_;
  OpType reg_type_;
};
}
