#include "DeclarationList.h"


void DeclarationList::AddDeclaration(Declaration* declaration) {
  declarations_.push_back(declaration);
}

void DeclarationList::Accept(Visitor* visitor) {
  visitor->Visit(this);
}