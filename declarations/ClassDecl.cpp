#include "ClassDecl.h"

#include <utility>

ClassDecl::ClassDecl(std::string identifier, DeclarationList* declaration_list)
    : identifier(std::move(identifier)), declaration_list_(declaration_list) {}

void ClassDecl::Accept(Visitor* visitor) {
  visitor->Visit(this);
}