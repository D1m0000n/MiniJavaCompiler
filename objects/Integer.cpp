#include "Integer.h"

Integer::Integer(int value) : value_(value) {}

int Integer::ToInt() {
  return value_;
}
std::string Integer::Type() {
  return "int";
}
