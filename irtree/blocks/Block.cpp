#include "Block.h"

void IRT::Block::SetLabel(IRT::LabelStatement* label) {
  label_ = label;
}

IRT::LabelStatement* IRT::Block::GetLabel() {
  return label_;
}

void IRT::Block::Add(IRT::Statement* statement) {
  statements_.push_back(statement);
}

std::vector<IRT::Statement*> IRT::Block::GetStatements() {
  return statements_;
}

void IRT::Block::SetJump(IRT::JumpStatement* jump) {
  jump_ = jump;
}

void IRT::Block::SetJump(IRT::JumpConditionalStatement* jump) {
  jump_ = jump;
}

IRT::Statement* IRT::Block::GetJump() {
  return jump_;
}
IRT::Block::Block() : label_(nullptr), jump_(nullptr), statements_(0) {}

