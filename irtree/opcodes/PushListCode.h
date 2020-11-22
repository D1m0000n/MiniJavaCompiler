#pragma once

#include "OpCode.h"
#include <vector>

namespace IRT {
class PushListCode : public OpCode {
 public:
  PushListCode(std::vector<int> registers);
  void Accept(OpCodeVisitor* visitor) override;
  void SetSuffix(std::string suffix) override;

  std::vector<int> registers_;
};
}  // namespace IRT