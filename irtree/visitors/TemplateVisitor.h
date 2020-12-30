#pragma once

#include "./Visitor.h"
#include "../nodes/BaseElement.h"
#include "../opcodes/OpCode.h"

namespace IRT {
template<typename T>
class TemplateVisitor : public Visitor {
 public:
  T Accept(BaseElement* element);
 protected:
  T tos_value_;

};

}  // namespace IRT


