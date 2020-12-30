#pragma once

#include <Declaration.h>
#include <ParamList.h>

#include <string>

class MethodDecl : public Declaration {
 public:
  MethodDecl(std::string  type, std::string  identifier, ParamList* param_list, AssignmentList* assignment_list);
  void Accept(Visitor* visitor);

  std::string type_;
  std::string identifier_;
  ParamList* param_list_;
  AssignmentList* assignment_list_;
};
