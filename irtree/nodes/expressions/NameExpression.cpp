#include "NameExpression.h"

namespace IRT {

void NameExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);

}
NameExpression::NameExpression(Label label) : label_(label) {

}

}