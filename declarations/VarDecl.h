#pragma once

#include "expressions/Expression.h"
#include "Declaration.h"

#include <string>

class VarDecl : public Declaration {
 public:
  VarDecl(std::string  type, std::string  variable);
  void Accept(Visitor* visitor) override;

  std::string type_;
  std::string variable_;
};