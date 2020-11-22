#pragma once

#include "OpCode.h"
#include <vector>

namespace IRT {
class PopListCode : public OpCode {
 public:
  PopListCode(std::vector<int> registers);
  void Accept(OpCodeVisitor* visitor) override;
  void SetSuffix(std::string suffix) override;

  std::vector<int> registers_;
};
}  // namespace IRT