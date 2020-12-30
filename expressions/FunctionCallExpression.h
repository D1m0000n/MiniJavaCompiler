#pragma once

#include "Expression.h"

#include <string>

class FunctionCallExpression : public Expression {
 public:
  FunctionCallExpression(Expression* expression, std::string name, ParamValueList* param_list);
  void Accept(Visitor* visitor) override;
  Expression* expression_;
  std::string name_;
  ParamValueList* param_list_;
};


