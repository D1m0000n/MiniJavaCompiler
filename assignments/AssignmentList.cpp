#include <AssignmentList.h>

void AssignmentList::AddAssignment(Assignment* assignment) {
  assignments_.push_back(assignment);
}

void AssignmentList::AcceptVisitor(Visitor* visitor) {
  visitor->Visit(this);
}