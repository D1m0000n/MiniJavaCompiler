#pragma once

#include "ConditionalWrapper.h"
namespace IRT {
class NegateConditionalWrapper : public ConditionalWrapper {
 public:
  explicit NegateConditionalWrapper(SubtreeWrapper* wrapper);
  Statement* ToConditional(Label true_label, Label false_label) override;
 private:
  SubtreeWrapper* wrapper_;
};

}  // namespace IRT


