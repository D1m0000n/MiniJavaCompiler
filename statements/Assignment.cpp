#include "Assignment.h"

#include <utility>

Assignment::Assignment(
    std::string variable,
    Expression* expression
) : variable_(std::move(variable)), expression_(expression) {}

void Assignment::Accept(Visitor* visitor) {
  visitor->Visit(this);
}