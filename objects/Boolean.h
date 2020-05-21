#pragma once

#include "Object.h"

class Boolean : public Object {
 public:
  explicit Boolean(int value);
  int ToBoolean() override;

 private:
  bool value_;
};