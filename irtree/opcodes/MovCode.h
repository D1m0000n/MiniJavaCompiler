#pragma once

#include "OpCode.h"

namespace IRT {
class MovCode : public OpCode {
 public:
  MovCode(
      std::string regd,
      OpType regd_tp,
      std::string arg,
      OpType arg_tp
  );
  void Accept(OpCodeVisitor* visitor) override;
  void SetSuffix(std::string suffix) override;

  std::string regd_;
  OpType regd_type_;
  std::string arg_;
  OpType arg_type_;
};
}  // namespace IRT
