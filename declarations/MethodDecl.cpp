#include "MethodDecl.h"

#include <utility>

MethodDecl::MethodDecl(
    std::string type,
    std::string identifier,
    ParamList* param_list,
    AssignmentList* assignment_list
)
    : type_(std::move(type)),
      identifier_(std::move(identifier)),
      param_list_(param_list),
      assignment_list_(assignment_list) {
}

void MethodDecl::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
