#include "SubCode.h"

IRT::SubCode::SubCode(std::string regd, std::string rega, std::string argb) : regd_(regd), rega_(rega), argb_(argb) {
  operation_ = "sub";
}

void IRT::SubCode::SetSuffix(std::string suffix) {
  suffix_ = suffix;
}
