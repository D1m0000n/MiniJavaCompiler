#include "MainClass.h"

MainClass::MainClass(std::string identifier, Statement* statement) : identifier(identifier), statement_(statement) {}

void MainClass::Accept(Visitor* visitor) {
  visitor->Visit(this);
}