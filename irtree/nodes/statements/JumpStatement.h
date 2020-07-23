#pragma once

#include "Statement.h"
#include "../../generators/Label.h"
namespace IRT {

class JumpStatement : public Statement {
 public:
  explicit JumpStatement(Label label);
  void Accept(Visitor* visitor) override;
  IRT::NodeType GetNodeType() override;

  Label label_;

};
}

