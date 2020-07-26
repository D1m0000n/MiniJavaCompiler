#include "AssemblyCodeGenerator.h"

void IRT::AssemblyCodeGenerator::Visit(IRT::ExpStatement* stmt) {
  stmt->GetExpression()->Accept(this);
}

void IRT::AssemblyCodeGenerator::Visit(IRT::ConstExpression* const_expression) {

}


