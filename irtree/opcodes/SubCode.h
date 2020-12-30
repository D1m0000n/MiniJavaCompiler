#pragma once

#include "OpCode.h"

namespace IRT {
class SubCode : public OpCode {
 public:
  SubCode(
      std::string regd,
      OpType regd_tp,
      std::string rega,
      OpType rega_tp,
      std::string argb,
      OpType argb_tp
  );
  void Accept(OpCodeVisitor* visitor) override;
  void SetSuffix(std::string suffix) override;

  std::string regd_;
  OpType regd_type_;
  std::string rega_;
  OpType rega_type_;
  std::string argb_;
  OpType argb_type_;
};
}  // namespace IRT
