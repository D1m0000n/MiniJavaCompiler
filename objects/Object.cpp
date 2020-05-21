#include "Object.h"

int Object::ToInt() {
  throw std::runtime_error("Integer type error");
}

int Object::ToBoolean() {
  throw std::runtime_error("Boolean type error");
}

Class Object::ToClass() {
  throw std::runtime_error("Class type error");
}

