#pragma once

#include "BaseElement.h"
#include <string>

class OpCode : public BaseElement {
 public:

  std::string operation_;
  std::string suffix_;
};