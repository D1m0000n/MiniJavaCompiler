#pragma once

#include <Declaration.h>
#include <BaseElement.h>
#include <vector>


class DeclarationList : public Declaration {
 public:
  void AddDeclaration(Declaration* declaration);
  void Accept(Visitor* visitor) override;

  std::vector<Declaration*> declarations_;
};
