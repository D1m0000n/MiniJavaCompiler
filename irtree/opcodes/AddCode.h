#pragma once

#include "OpCode.h"

class AddCode : public OpCode {

  AddCode(std::string regd, std::string rega, std::string argb);
  void SetSuffix(std::string suffix);

  std::string regd_;
  std::string rega_;
  std::string argb_;
};