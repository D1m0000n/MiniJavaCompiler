#pragma once

#include <MainClass.h>
#include <DeclarationList.h>

class Program {
 public:
  Program(MainClass* main_class, DeclarationList* declaration_list);

  MainClass* main_class_;
  DeclarationList* class_declarations_;

  void Accept(Visitor* visitor);
};