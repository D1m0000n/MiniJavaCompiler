#pragma once

#include "Expression.h"
#include "../../generators/Label.h"
namespace IRT {
class NameExpression : public Expression {
 public:
  NameExpression(Label label);
  void Accept(Visitor* visitor) override;
  Label label_;
};

}


