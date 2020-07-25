#pragma once

#include "TemplateVisitor.h"
#include "VisitorStruct.h"
#include "BaseElements.h"

#include <vector>

namespace IRT {
class EseqEliminateVisitor : public TemplateVisitor<IrtStorage> {
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

  struct IRList {
    IRList() {
      exp_list = new ExpressionList();
      statements.resize(0);
    }
    void MakeStatementList();
    void AddStatement(Statement* statement);
    void SetStatement(Statement* statement);

    IRT::Statement* suffix;
    IRT::ExpressionList* exp_list;
    std::vector<IRT::Statement*> statements;
  };

 public:
  Statement* GetTree();
};

}


