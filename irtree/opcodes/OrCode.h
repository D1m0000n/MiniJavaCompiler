#pragma once

#include "OpCode.h"

class OrCode : public OpCode {

  OrCode(std::string regd, std::string rega, std::string argb);
  void SetSuffix(std::string suffix);

  std::string regd_;
  std::string rega_;
  std::string argb_;
};