#include "MethodDecl.h"

#include <utility>

MethodDecl::MethodDecl(std::string type, std::string ide) : type_(std::move(type)), identifier_(std::move(ide)) {
}

void MethodDecl::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
