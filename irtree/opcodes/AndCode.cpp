#include "AndCode.h"

IRT::AndCode::AndCode(std::string regd, std::string rega, std::string argb) : regd_(regd), rega_(rega), argb_(argb) {
  operation_ = "and";
}

void IRT::AndCode::SetSuffix(std::string suffix) {
  suffix_ = suffix;
}