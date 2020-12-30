#include "Program.h"

Program::Program(MainClass* main_class, DeclarationList* declaration_list)
    : main_class_(main_class), class_declarations_(declaration_list) {}

void Program::Accept(Visitor* visitor) {
  visitor->Visit(this);
}