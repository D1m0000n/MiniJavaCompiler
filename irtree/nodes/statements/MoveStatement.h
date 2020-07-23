#pragma once

#include "Statement.h"
#include "../expressions/Expression.h"
namespace IRT {

class MoveStatement : public Statement {
 public:
  MoveStatement(Expression* source, Expression* target);
  void Accept(Visitor* visitor) override;
  IRT::NodeType GetNodeType() override;

  Expression* source_;
  Expression* target_;
};

};


