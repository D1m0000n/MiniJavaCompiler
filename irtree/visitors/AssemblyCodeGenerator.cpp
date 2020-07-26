#include "AssemblyCodeGenerator.h"

void IRT::AssemblyCodeGenerator::Visit(IRT::ExpStatement* stmt) {
  stmt->GetExpression()->Accept(this);
}

void IRT::AssemblyCodeGenerator::Visit(IRT::ConstExpression* const_expression) {
  Temporary T;
  std::string reg = T.ToString();
  std::string const_str = "#" + std::to_string(const_expression->Value());
  IRT::MovCode* mov_code = new IRT::MovCode(reg, const_str);
  op_codes_.push_back(mov_code);
  tos_value_ = reg;
}

std::vector<IRT::OpCode*> IRT::AssemblyCodeGenerator::GetOpCodes() {
  return op_codes_;
}


