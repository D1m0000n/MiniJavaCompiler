#pragma once

#include <vector>
#include "BaseElement.h"

namespace IRT {
class Expression;
class ExpressionList : public BaseElement {
 public:
  ExpressionList() = default;

  void Add(Expression* expression);
  void Accept(Visitor* visitor) override;
  IRT::NodeType GetNodeType() override;

  std::vector<Expression*> expressions_;

};

}  // namespace IRT

