#include "Trace.h"

void IRT::Trace::AddNextBlock(IRT::Block block) {
  block_sequence_.push_back(block);
}

std::vector<IRT::Block>& IRT::Trace::GetBlockSequence() {
  return block_sequence_;
}
