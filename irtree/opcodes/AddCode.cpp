#include "AddCode.h"

IRT::AddCode::AddCode(std::string regd, std::string rega, std::string argb) : regd_(regd), rega_(rega), argb_(argb) {
  operation_ = "add";
}

void IRT::AddCode::SetSuffix(std::string suffix) {
  suffix_ = suffix;
}
