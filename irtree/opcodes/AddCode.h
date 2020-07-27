#pragma once

#include "OpCode.h"

namespace IRT{
class AddCode : public OpCode {

  AddCode(
      std::string regd,
      OpType regd_tp,
      std::string rega,
      OpType rega_tp,
      std::string argb,
      OpType argb_tp
      );

  void SetSuffix(std::string suffix);

  std::string regd_;
  OpType regd_type_;
  std::string rega_;
  OpType rega_type_;
  std::string argb_;
  OpType argb_type_;
};
}
