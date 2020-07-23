#pragma once

#include "../nodes/statements/LabelStatement.h"
#include "../nodes/statements/Statement.h"
#include "../nodes/statements/JumpStatement.h"
#include "../nodes/statements/JumpConditionalStatement.h"

#include <vector>

namespace IRT {

class Block {
 public:
  Block();

  void SetLabel(LabelStatement* label);
  LabelStatement* GetLabel();
  void Add(Statement* statement);
  std::vector<Statement*> GetStatements();
  void SetJump(JumpStatement* jump);
  void SetJump(JumpConditionalStatement* jump);
  Statement* GetJump();

 private:
  LabelStatement* label_;
  Statement* jump_;
  std::vector<Statement*> statements_;
};
}
