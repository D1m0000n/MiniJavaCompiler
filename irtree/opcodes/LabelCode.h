#pragma once

#include "OpCode.h"

namespace IRT {
class LabelCode : public OpCode {
 public:
  LabelCode(std::string label);
  void Accept(OpCodeVisitor* visitor) override;
  void SetSuffix(std::string kek) override;

  std::string label_;
};
}  // namespace IRT
