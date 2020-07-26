#include "AddCode.h"

AddCode::AddCode(std::string regd, std::string rega, std::string argb) : regd_(regd), rega_(rega), argb_(argb) {
  operation_ = "add";
}

void AddCode::SetSuffix(std::string suffix) {
  suffix_ = suffix;
}
