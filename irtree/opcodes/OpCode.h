#pragma once

#include "BaseElement.h"
#include <string>

namespace IRT{
enum class OpType : char {
  TEMP,
  CONST,
  REG,
  NONE
};

class OpCode {
 public:
//  OpCode() = default;
  std::string operation_;
  std::string suffix_;
};
}
