#pragma once

#include "BaseElement.h"
#include <string>

namespace IRT{
class OpCode {
 public:
//  OpCode() = default;
  std::string operation_;
  std::string suffix_;
};
}
