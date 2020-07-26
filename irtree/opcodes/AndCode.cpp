#include "AndCode.h"

AndCode::AndCode(std::string regd, std::string rega, std::string argb) : regd_(regd), rega_(rega), argb_(argb) {
  operation_ = "and";
}

void AndCode::SetSuffix(std::string suffix) {
  suffix_ = suffix;
}