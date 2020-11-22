#pragma once

#include "Object.h"

class ClassType : public Object {
 public:
  explicit ClassType(std::string type);
  std::string Type() override;

  std::string type;
};