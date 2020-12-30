#pragma once

#include "../blocks/Block.h"

#include <vector>

namespace IRT {

class Trace {
 public:
  void AddNextBlock(Block block);
  std::vector<Block>& GetBlockSequence();

  std::vector<Block> block_sequence_;
};
}  // namespace IRT