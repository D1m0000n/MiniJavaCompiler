#pragma once

#include "OpCode.h"

namespace IRT{
class MovCode : public OpCode {
 public:
  MovCode(std::string regd, std::string arg);
  void SetSuffix(std::string suffix);

  std::string regd_;
  std::string arg_;
};
}
