#include "ReturnStatement.h"

void ReturnStatement::Accept(Visitor *visitor) {
  visitor->Visit(this);
}

ReturnStatement::ReturnStatement(Expression *expression): return_expression_(expression) {

}
