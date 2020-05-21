#include "Boolean.h"

Boolean::Boolean(int value) : value_(value) {}

int Boolean::ToBoolean() {
  return value_ > 0 ? 1 : 0;
}