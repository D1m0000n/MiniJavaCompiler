#include "Class.h"

ClassType::ClassType(std::string type) : type(type) {
  if (type == "int" || type == "boolean" || type == "void") {
    throw std::runtime_error("Wrong class identifier");
  }
}

//Class ClassType::ToClass() { return {}; }

std::string ClassType::Type() {
  return type;
}
