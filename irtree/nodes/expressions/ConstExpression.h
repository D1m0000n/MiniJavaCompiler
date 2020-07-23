#pragma once

#include "Expression.h"
namespace IRT {

class ConstExpression : public Expression {
 public:
  explicit ConstExpression(int value);
  ~ConstExpression() final = default;
  int Value() const;

  void Accept(Visitor* visitor) override;
  IRT::NodeType GetNodeType() override;

 private:
  int value_;
};

}

