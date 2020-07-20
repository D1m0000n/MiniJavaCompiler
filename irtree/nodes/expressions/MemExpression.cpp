#include "MemExpression.h"

namespace IRT {

void MemExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);

}
MemExpression::MemExpression(Expression* expression) : expression_(expression) {

}
}