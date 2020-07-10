#pragma once

#include <Expression.h>
#include <Statement.h>
#include <memory>
#include <vector>
#include <string>

class MethodInvExpression : public Expression, public Statement {
 public:
  MethodInvExpression(Expression* expr, std::string identifier,
                      std::vector<Expression*> expr_list);
  int eval() const override;
  void Accept(Visitor* visitor) override;
  Expression* expression_;
  std::string identifier_;
  std::vector<Expression*> expression_list_;
};