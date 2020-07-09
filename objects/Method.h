#pragma once

#include "Object.h"

#include <vector>
#include <string>

class Method : public Object {
 public:
  Method(const std::vector<std::string>& argumen_names);

  std::vector<Object*> arguments_;
  std::vector<std::string> argument_names_;
};