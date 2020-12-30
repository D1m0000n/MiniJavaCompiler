#include "VarDecl.h"

#include <utility>

VarDecl::VarDecl(
    std::string  type,
    std::string  variable
) : type_(std::move(type)), variable_(std::move(variable)) {}


void VarDecl::Accept(Visitor* visitor) {
    visitor->Visit(this);
}