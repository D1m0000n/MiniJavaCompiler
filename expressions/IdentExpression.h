#pragma once
#include <Expression.h>

#include <string>

class IdentExpression : public Expression {
 public:
  IdentExpression(std::string ident);
  [[nodiscard]] int eval() const override;
  void AcceptVisitor(Visitor* visitor) override;

  std::string ident_;
};