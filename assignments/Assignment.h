#pragma once

#include <Expression.h>
#include <BaseElement.h>

#include <string>

class Assignment : public BaseElement {
 public:
  Assignment(std::string variable, Expression* expression);
  void AcceptVisitor(Visitor* visitor) override;

  std::string variable_;
  Expression* expression_;
};