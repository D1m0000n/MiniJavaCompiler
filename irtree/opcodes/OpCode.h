#pragma once

#include <string>
#include "../visitors/OpCodeVisitor.h"

namespace IRT{
enum class OpType : char {
  TEMP,
  CONST,
  REG,
  NONE,
  NAME,
  FP
};

class OpCode {
 public:
  OpCode() = default;
  virtual void SetSuffix(std::string) = 0;
  virtual void Accept(OpCodeVisitor* visitor) = 0;

  std::string operation_;
  std::string suffix_;
};
}
