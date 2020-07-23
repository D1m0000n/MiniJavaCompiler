#pragma once
#include "Statement.h"
#include "../../generators/Label.h"
namespace IRT {

class LabelStatement : public Statement {
 public:
  explicit LabelStatement(IRT::Label label);
  void Accept(Visitor* visitor) override;
  IRT::NodeType GetNodeType() override;

  Label label_;
};

}

