#include "Object.h"

int Object::ToInt() {
  throw std::runtime_error("Integer type error");
}

int Object::ToBoolean() {
  throw std::runtime_error("Boolean type error");
}

std::string Object::Type() {
  return std::string();
}

