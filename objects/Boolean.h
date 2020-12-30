#pragma once

#include "Object.h"

class Boolean : public Object {
 public:
  explicit Boolean(int value);
  int ToBoolean() override;
  std::string Type() override;

 private:
  bool value_;
};