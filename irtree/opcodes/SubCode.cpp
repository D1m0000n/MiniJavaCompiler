#include "SubCode.h"

SubCode::SubCode(std::string regd, std::string rega, std::string argb) : regd_(regd), rega_(rega), argb_(argb) {
  operation_ = "sub";
}

void SubCode::SetSuffix(std::string suffix) {
  suffix_ = suffix;
}
