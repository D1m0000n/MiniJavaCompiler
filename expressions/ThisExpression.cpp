#include "ThisExpression.h"

void ThisExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
