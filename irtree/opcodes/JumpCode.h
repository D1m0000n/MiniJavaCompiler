#pragma once

#include "OpCode.h"

namespace IRT {
class JumpCode : public OpCode {
 public:
  JumpCode(std::string label);
  void Accept(OpCodeVisitor* visitor) override;
  void SetSuffix(std::string suffix) override;

  std::string label_;
};
}  // namespace IRT
