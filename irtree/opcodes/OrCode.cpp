#include "OrCode.h"

IRT::OrCode::OrCode(std::string regd, std::string rega, std::string argb) : regd_(regd), rega_(rega), argb_(argb) {
  operation_ = "or";
}

void IRT::OrCode::SetSuffix(std::string suffix) {
  suffix_ = suffix;
}
