#pragma once

#include "OpCode.h"

namespace IRT{
class MovCode : public OpCode {
 public:
  MovCode(
      std::string regd,
      OpType regd_tp,
      std::string arg,
      OpType arg_tp
      );
  void SetSuffix(std::string suffix);

  std::string regd_;
  OpType regd_type_;
  std::string arg_;
  OpType arg_type_;
};
}
