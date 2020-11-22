#pragma once

#include "Statement.h"
#include "../expressions/Expression.h"

namespace IRT {
class PrintStatement : public Statement {
 public:
  PrintStatement(Expression* expression);
  ~PrintStatement() override = default;
  void Accept(Visitor* visitor) override;
  IRT::NodeType GetNodeType() override;

  Expression* expression_;
};

}  // namespace IRT
