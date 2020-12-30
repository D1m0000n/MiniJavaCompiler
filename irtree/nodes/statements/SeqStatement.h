#pragma once
#include "Statement.h"

namespace IRT {
class SeqStatement : public Statement {
 public:
  SeqStatement(Statement* first, Statement* second);
  void Accept(Visitor* visitor) override;
  IRT::NodeType GetNodeType() override;

  Statement* first_statement_;
  Statement* second_statement_;
};

}  // namespace IRT


