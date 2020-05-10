#pragma once

#include <Visitor.h>

class BaseElement {
 public:
  virtual void AcceptVisitor(Visitor* visitor) = 0;
  virtual ~BaseElement() = default;
};
