#pragma once

#include "../nodes/expressions/Expression.h"
#include "../nodes/statements/Statement.h"
namespace IRT {

struct IrtStorage {
  Expression* expression_ = nullptr;
  Statement* statement_ = nullptr;
  ExpressionList* expression_list_ = nullptr;
};
}  // namespace IRT
