#include "MethodDecl.h"

#include <utility>

MethodDecl::MethodDecl(
    std::string type,
    std::string ide,
    ParamList* param_list,
    AssignmentList* assignment_list
)
    : type_(std::move(type)),
      identifier_(std::move(ide)),
      param_list_(param_list),
      assignment_list_(assignment_list) {
}

void MethodDecl::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
