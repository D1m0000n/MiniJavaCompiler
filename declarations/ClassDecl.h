#pragma once

#include <Declaration.h>

#include <string>

class ClassDecl : public Declaration {
 public:
  ClassDecl(std::string identifier, DeclarationList* declaration_list);

  void Accept(Visitor* visitor) override;

  std::string identifier;
  DeclarationList* declaration_list_;
};