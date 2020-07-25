#include "LinearizeVisitor.h"

void IRT::LinearizeVisitor::Visit(IRT::ExpStatement* exp_stmt) {
  Expression* expr = Accept(exp_stmt->GetExpression()).expression_;
  tos_value_.statement_ = new ExpStatement(expr);
}

void IRT::LinearizeVisitor::Visit(ConstExpression* const_expr) {
  tos_value_.expression_ = new ConstExpression(const_expr->Value());
}

void IRT::LinearizeVisitor::Visit(JumpConditionalStatement* statement) {
  Expression* left_expr = Accept(statement->left_operand_).expression_;
  Expression* right_expr = Accept(statement->right_operand_).expression_;

  JumpConditionalStatement* result_stmt = new JumpConditionalStatement(
      statement->operator_type_,
      left_expr,
      right_expr,
      statement->label_true_,
      statement->label_false_
  );
  tos_value_.statement_ = result_stmt;
}

void IRT::LinearizeVisitor::Visit(MoveStatement* statement) {
  Expression* source_expr = Accept(statement->source_).expression_;
  Expression* target_expr = Accept(statement->target_).expression_;
  MoveStatement* result_stmt = new MoveStatement(source_expr, target_expr);
  tos_value_.statement_ = result_stmt;
}

void IRT::LinearizeVisitor::Visit(SeqStatement* statement) {
  Statement* first_stmt = Accept(statement->first_statement_).statement_;
  //// Re-hang nodes
  if (first_stmt->GetNodeType() == IRT::NodeType::SEQ) {
    SeqStatement* seq_stmt = dynamic_cast<SeqStatement*>(first_stmt);
    statement->second_statement_ = new SeqStatement(
        seq_stmt->second_statement_,
        statement->second_statement_
    );
    first_stmt = seq_stmt->first_statement_;
  }
  Statement* second_stmt = Accept(statement->second_statement_).statement_;
  SeqStatement* result_stmt = new SeqStatement(first_stmt, second_stmt);
  tos_value_.statement_ = result_stmt;
}

void IRT::LinearizeVisitor::Visit(LabelStatement* statement) {
  tos_value_.statement_ = new LabelStatement(statement->label_);
}

void IRT::LinearizeVisitor::Visit(BinopExpression* expression) {
  Expression* first_expr = Accept(expression->first_).expression_;
  Expression* second_expr = Accept(expression->second_).expression_;
  Expression* result_expr = new BinopExpression(
      expression->operator_type_,
      first_expr,
      second_expr
  );
  tos_value_.expression_ = result_expr;
}

void IRT::LinearizeVisitor::Visit(TempExpression* expression) {
  tos_value_.expression_ = new TempExpression(expression->temporary_);
}

void IRT::LinearizeVisitor::Visit(MemExpression* expression) {
  Expression* expr = Accept(expression->expression_).expression_;
  tos_value_.expression_ = new MemExpression(expr);
}

void IRT::LinearizeVisitor::Visit(JumpStatement* statement) {
  tos_value_.statement_ = new JumpStatement(statement->label_);
}

void IRT::LinearizeVisitor::Visit(CallExpression* expression) {
  Expression* expr = Accept(expression->function_name_).expression_;
  ExpressionList* list_expr = Accept(expression->args_).expression_list_;
  tos_value_.expression_ = new CallExpression(expr, list_expr);
}

void IRT::LinearizeVisitor::Visit(ExpressionList* expression_list) {
  tos_value_.expression_list_ = new ExpressionList();
  for (auto& expression : expression_list->expressions_) {
    tos_value_.expression_list_->Add(Accept(expression).expression_);
  }
}

void IRT::LinearizeVisitor::Visit(NameExpression* expression) {
  tos_value_.expression_ = new NameExpression(expression->label_);
}

void IRT::LinearizeVisitor::Visit(EseqExpression* expression) {
}

void IRT::LinearizeVisitor::Visit(PrintStatement* print_statement) {
  IrtStorage elements = Accept(print_statement->expression_);
  tos_value_.statement_ = new IRT::PrintStatement(elements.expression_);
}

IRT::Statement* IRT::LinearizeVisitor::GetTree() {
  return tos_value_.statement_;
}
