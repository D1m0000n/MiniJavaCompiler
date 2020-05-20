#pragma once

#include "expressions/Expression.h"
#include "Statement.h"

#include <string>

class VarDecl: public Statement {
 public:
    VarDecl(const std::string& variable);
    void Accept(Visitor* visitor) override;

    std::string variable_;
};