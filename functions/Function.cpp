#include "Function.h"

#include <utility>

void Function::Accept(Visitor *visitor) {
  visitor->Visit(this);
}

Function::Function(
    std::string type,
    std::string name,
    ParamList *param_list,
    AssignmentList *statements): type_(std::move(type)), name_(std::move(name)), param_list_(param_list), statements_(statements){
}
