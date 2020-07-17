#pragma once

#include <Declaration.h>

#include <statements/AssignmentList.h>
#include <functions/ParamList.h>
#include <string>

class Function : public Declaration {
 public:
  Function(std::string type, std::string name, ParamList* param_list, AssignmentList* statements);
  void Accept(Visitor *visitor) override;

  std::string type_;
  std::string name_;
  ParamList* param_list_;
  AssignmentList* statements_;
};



