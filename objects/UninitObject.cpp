#include "UninitObject.h"

#include <stdexcept>
#include <utility>

UninitObject::UninitObject(std::string type) : type_(std::move(type)) {}

int UninitObject::ToInt() {
  throw std::runtime_error("Variable not initialized");
}
std::string UninitObject::Type() {
  return type_;
}
