#pragma once

#include "Object.h"

class UninitObject : public Object {
 public:
  UninitObject(std::string type);
  int ToInt() override;
  std::string Type() override;
  std::string type_;
};