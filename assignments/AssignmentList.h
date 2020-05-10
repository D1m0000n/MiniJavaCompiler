#pragma once

#include <Assignment.h>
#include <BaseElement.h>
#include <vector>

class AssignmentList : public BaseElement {
 public:
  void AddAssignment(Assignment* assignment);
  void AcceptVisitor(Visitor* visitor) override;

  std::vector<Assignment*> assignments_;
};