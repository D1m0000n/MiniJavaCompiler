#pragma once

#include <BaseElement.h>
#include <Statement.h>

#include <string>
#include <vector>

class MainClass : public BaseElement {
 public:
  MainClass(std::string identifier, AssignmentList* statement);
  void Accept(Visitor* visitor) override;

  std::string identifier;
  AssignmentList* statements_;
};