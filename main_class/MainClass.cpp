#include "MainClass.h"

MainClass::MainClass(std::string identifier, AssignmentList* statement) : identifier(identifier), statements_(statement) {}

void MainClass::Accept(Visitor* visitor) {
  visitor->Visit(this);
}