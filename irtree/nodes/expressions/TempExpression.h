#pragma once

#include "../expressions/Expression.h"
#include "../../generators/Temporary.h"
namespace IRT {
class TempExpression : public Expression {
 public:
  explicit TempExpression(const IRT::Temporary& temporary);
  void Accept(Visitor* visitor) override;
  IRT::NodeType GetNodeType() override;

  Temporary temporary_;
};

}


