#pragma once

//#include "statements/AssignmentList.h"
#include <MainClass.h>

class Program {
 public:
  Program(MainClass* main_class);
  MainClass* main_class_;

  void Accept(Visitor* visitor);
};