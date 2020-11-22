#pragma once

#include "Statement.h"
#include "../expressions/Expression.h"

namespace IRT {
class ExpStatement : public Statement {
 public:
  explicit ExpStatement(Expression* expression);
  Expression* GetExpression();
  ~ExpStatement() override = default;
  void Accept(Visitor* visitor) override;
  IRT::NodeType GetNodeType() override;

 private:
  Expression* expression_;
};

}  // namespace IRT

