#pragma once

#include "TemplateVisitor.h"
#include "VisitorStruct.h"
#include "BaseElements.h"

#include <vector>
#include <algorithm>
#include <stdexcept>


namespace IRT {
 class AssemblyCodeGenerator : public TemplateVisitor<std::pair<std::string, IRT::OpType>> {
 public:
  void Visit(ExpStatement* stmt) override;
  void Visit(ConstExpression* const_expression) override;
  void Visit(JumpConditionalStatement* jump_conditional_statement) override;
  void Visit(MoveStatement* move_statement) override;
  void Visit(SeqStatement* seq_statement) override;
  void Visit(LabelStatement* label_statement) override;
  void Visit(BinopExpression* binop_statement) override;
  void Visit(TempExpression* temp_exression) override;
  void Visit(MemExpression* mem_expression) override;
  void Visit(JumpStatement* jump_statement) override;
  void Visit(CallExpression* call_expression) override;
  void Visit(ExpressionList* expression_list) override;
  void Visit(NameExpression* name_expression) override;
  void Visit(EseqExpression* eseq_expression) override;
  void Visit(PrintStatement* print_statement) override;

  void MakeBinOperation(
      std::string regd,
      OpType regd_tp,
      std::string rega,
      OpType rega_tp,
      std::string argb,
      OpType argb_tp,
      IRT::BinaryOperatorType operator_type
      );

  int CountConst(int first, int second, IRT::BinaryOperatorType operator_type);

 public:
  std::vector<OpCode*> GetCodes();
  std::vector<OpCode*> op_codes_;
};

}


