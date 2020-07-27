#include "LabelCode.h"

IRT::LabelCode::LabelCode(std::string label) : label_(label) {
  operation_ = "";
}

void IRT::LabelCode::SetSuffix(std::string kek) {}

void IRT::LabelCode::Accept(IRT::OpCodeVisitor* visitor) {
  visitor->Visit(this);
}
