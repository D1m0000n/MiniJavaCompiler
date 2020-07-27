#pragma once

#include "OpCode.h"

namespace IRT {
class LdrCode : public OpCode {
 public:
  LdrCode(
      std::string regd,
      OpType regd_tp,
      std::string regaddr,
      OpType regaddr_tp,
      int shift
  );
  void Accept(OpCodeVisitor* visitor) override;
  void SetSuffix(std::string suffix) override;

  std::string regd_;
  OpType regd_type_;
  std::string regaddr_;
  OpType regaddr_type_;

  int offset_;

};
}
