#pragma once

#include "OpCode.h"

namespace IRT{
class CmpCode : public OpCode {
 public:

  CmpCode(
      std::string rega,
      OpType rega_tp,
      std::string argb,
      OpType argb_tp
      );

  void Accept(OpCodeVisitor* visitor) override;
  void SetSuffix(std::string suffix) override;

  std::string rega_;
  OpType rega_type_;
  std::string argb_;
  OpType argb_type_;
};
}  // namespace IRT
