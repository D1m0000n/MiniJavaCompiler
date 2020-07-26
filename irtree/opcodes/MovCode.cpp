#include "MovCode.h"

IRT::MovCode::MovCode(std::string regd, std::string arg) : regd_(regd), arg_(arg) {
  operation_ = "mov";
}

void IRT::MovCode::SetSuffix(std::string suffix) {
  suffix_ = suffix;
}
