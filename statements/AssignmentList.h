#pragma once

#include "statements/Statement.h"
#include "base_elements/BaseElement.h"
#include <vector>

class AssignmentList : public Statement {
 public:
    void AddStatement(Statement* assignment);
    void Accept(Visitor* visitor) override;

    std::vector<Statement*> statements_;
};