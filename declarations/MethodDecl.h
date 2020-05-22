#pragma once

#include <Declaration.h>

#include <string>

class MethodDecl : public Declaration {
 public:
  MethodDecl(std::string  type, std::string  identifier);
  void Accept(Visitor* visitor);

  std::string type_;
  std::string identifier_;
};
