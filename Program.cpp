#include "Program.h"

Program::Program(MainClass* main_class) : main_class_(main_class) {}

void Program::Accept(Visitor *visitor) {
  visitor->Visit(this);
}