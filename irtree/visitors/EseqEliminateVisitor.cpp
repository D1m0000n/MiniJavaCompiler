#include "EseqEliminateVisitor.h"

void IRT::EseqEliminateVisitor::Visit(ConstExpression* const_exp) { //// OK
  tos_value_.expression_ = new ConstExpression(const_exp->Value());
}

void IRT::EseqEliminateVisitor::Visit(JumpConditionalStatement* jump_cond_stmt) { //// OK
  IrtStorage left_elements = Accept(jump_cond_stmt->left_operand_);
  IrtStorage right_elements = Accept(jump_cond_stmt->right_operand_);
  IRT::Expression* left_side = left_elements.expression_;
  IRT::Expression* right_side = right_elements.expression_;

  if (left_side->GetNodeType() == IRT::NodeType::ESEQ) {
    EseqExpression* left_eseq = dynamic_cast<EseqExpression*>(left_side);

    if (right_side->GetNodeType() == IRT::NodeType::ESEQ) { //// L - ESEQ, R - ESEQ
      EseqExpression* right_eseq = dynamic_cast<EseqExpression*>(right_side);
      Temporary T;

      SeqStatement* result_stmt = new SeqStatement(
          left_eseq->statement_,
          new SeqStatement(
              new MoveStatement(
                  left_eseq->expression_,
                  new TempExpression(T)
              ),
              new SeqStatement(
                  right_eseq->statement_,
                  new JumpConditionalStatement(
                      jump_cond_stmt->operator_type_,
                      new TempExpression(T),
                      right_eseq->expression_,
                      jump_cond_stmt->label_true_,
                      jump_cond_stmt->label_false_
                  )
              )
          )
      );
      tos_value_.statement_ = result_stmt;
    } else { //// L - ESEQ, R - not ESEQ
      SeqStatement* result_stmt = new SeqStatement(
          left_eseq->statement_,
          new JumpConditionalStatement(
              jump_cond_stmt->operator_type_,
              left_eseq->expression_,
              right_side,
              jump_cond_stmt->label_true_,
              jump_cond_stmt->label_false_
          )
      );
      tos_value_.statement_ = result_stmt;
    }
  } else {
    if (right_side->GetNodeType() == IRT::NodeType::ESEQ) { //// L - not ESEQ, R - ESEQ
      EseqExpression* right_eseq = dynamic_cast<EseqExpression*>(right_side);
      Temporary T;

      SeqStatement* result_stmt = new SeqStatement(
          new MoveStatement(left_side,
                            new TempExpression(T)
          ),
          new SeqStatement(
              right_eseq->statement_,
              new JumpConditionalStatement(
                  jump_cond_stmt->operator_type_,
                  new TempExpression(T),
                  right_eseq->expression_,
                  jump_cond_stmt->label_true_,
                  jump_cond_stmt->label_false_
              )
          )
      );
      tos_value_.statement_ = result_stmt;
    } else { //// L - not ESEQ, R - not ESEQ
      JumpConditionalStatement* result_stmt = new JumpConditionalStatement(
          jump_cond_stmt->operator_type_,
          left_side,
          right_side,
          jump_cond_stmt->label_true_,
          jump_cond_stmt->label_false_
      );
      tos_value_.statement_ = result_stmt;
    }
  }
}

bool IsConst(IRT::Statement* statement) {
  if (statement->GetNodeType() != IRT::NodeType::EXP) {
    return false;
  } else {
    IRT::ExpStatement* exp_statement = dynamic_cast<IRT::ExpStatement*>(statement);
    bool result = (exp_statement->GetNodeType() == IRT::NodeType::CONST);
    return result;
  }
}

bool IsConst(IRT::Expression* expression) {
  bool result = (expression->GetNodeType() == IRT::NodeType::CONST) ||
      (expression->GetNodeType() == IRT::NodeType::NAME);
  return result;
}

IRT::EseqEliminateVisitor::IRList ShiftEseq(IRT::ExpressionList* expression_list) {
  size_t list_size = expression_list->expressions_.size();
  size_t check_index = 0;
  IRT::EseqEliminateVisitor::IRList ir_list;
  auto& list_of_expressions = ir_list.exp_list->expressions_;
  list_of_expressions.resize(list_size);

  for (size_t i = 0; i < list_size; ++i) { //// main loop of shifts
    //// found not ESEQ node
    if (IRT::NodeType::ESEQ != expression_list->expressions_[i]->GetNodeType()) {
      list_of_expressions[i] = expression_list->expressions_[i];
      continue;
    }

    //// found ESEQ node, cast to continue checking
    IRT::EseqExpression* eseq = dynamic_cast<IRT::EseqExpression*>(expression_list->expressions_[i]);

    //// If const, just take expression
    if (IsConst(eseq->statement_)) {
      list_of_expressions[i] = eseq->expression_;
      ir_list.AddStatement(eseq->statement_);
      continue;
    }

    //// Continue checking from last unchecked pointer
    while (check_index < i) {
      IRT::Temporary T;
      //// Is const
      if (IsConst(list_of_expressions[check_index])) continue;

      ir_list.AddStatement(
          new IRT::MoveStatement(
              list_of_expressions[check_index],
              new IRT::TempExpression(T)
          )
      );
      list_of_expressions[check_index] = new IRT::TempExpression(T);

      ++check_index;
    }

    list_of_expressions[i] = eseq->expression_;
    ir_list.AddStatement(eseq->statement_);
  }

  //// Can't call .back() from empty vector
  if (ir_list.statements.empty()) {
    ir_list.SetStatement(
        new IRT::ExpStatement(
            new IRT::ConstExpression(0)
        )
    );
  } else {
    ir_list.MakeStatementList();
  }
  return ir_list;
}
//// shas zdohnu((
void IRT::EseqEliminateVisitor::Visit(MoveStatement* move_statement) {
  IrtStorage source_elements = Accept(move_statement->source_);
  IrtStorage target_elements = Accept(move_statement->target_);
  Expression* source_expr = source_elements.expression_;
  Expression* target_expr = target_elements.expression_;

  if (target_expr->GetNodeType() == IRT::NodeType::MEM &&
      source_expr->GetNodeType() == IRT::NodeType::ESEQ) { //// 1 (ESEQ + MEM)
    EseqExpression* eseq_expr = dynamic_cast<EseqExpression*>(source_expr);
    MemExpression* mem_expr = dynamic_cast<MemExpression*>(target_expr);

    if (IsConst(eseq_expr->expression_) || IsConst(mem_expr->expression_)) {
      Statement* result_stmt = new SeqStatement(
          eseq_expr->statement_,
          new MoveStatement(
              eseq_expr->expression_,
              new MemExpression(mem_expr->expression_)
          )
      );
      tos_value_.statement_ = result_stmt;
      return;
    }
    Temporary T;
    SeqStatement* result_stmt = new SeqStatement(
        new MoveStatement(
            mem_expr->expression_,
            new TempExpression(T)
        ),
        new SeqStatement(
            eseq_expr->statement_,
            new MoveStatement(
                eseq_expr->expression_,
                new MemExpression(
                    new TempExpression(T)
                )
            )
        )
    );
    tos_value_.statement_ = result_stmt;
    return;
  }

  if (source_expr->GetNodeType() == IRT::NodeType::CALL &&
      target_expr->GetNodeType() == IRT::NodeType::TEMP) { //// 2(CALL + TEMP)
    CallExpression* call_expr = dynamic_cast<CallExpression*>(source_expr);
    TempExpression* temp_expr = dynamic_cast<TempExpression*>(target_expr);

    auto ir_list = ShiftEseq(call_expr->args_);
    if (call_expr->function_name_->GetNodeType() == IRT::NodeType::ESEQ) {
      EseqExpression* eseq_expr = dynamic_cast<EseqExpression*>(call_expr->function_name_);
      SeqStatement* result_stmt = new SeqStatement(
          eseq_expr->statement_,
          new SeqStatement(
              ir_list.suffix,
              new MoveStatement(
                  new CallExpression(
                      eseq_expr->expression_,
                      ir_list.exp_list
                  ),
                  new TempExpression(
                      temp_expr->temporary_
                  )
              )
          )
      );
      tos_value_.statement_ = result_stmt;
      return;
    } else {
      SeqStatement* result_stmt = new SeqStatement(
          ir_list.suffix,
          new MoveStatement(
              new CallExpression(
                  call_expr->function_name_,
                  ir_list.exp_list
              ),
              new TempExpression(temp_expr->temporary_)
          )
      );
      tos_value_.statement_ = result_stmt;
      return;
    }
  }

  if (target_expr->GetNodeType() == IRT::NodeType::MEM) { //// 3 (MEM->ESEQ)
    MemExpression* mem_expr = dynamic_cast<MemExpression*>(target_expr);
    if (mem_expr->expression_->GetNodeType() == IRT::NodeType::ESEQ) {
      EseqExpression* eseq_expr = dynamic_cast<EseqExpression*>(mem_expr->expression_);

      if (IsConst(source_expr) || IsConst(eseq_expr->statement_)) {
        SeqStatement* result_stmt = new SeqStatement(
            eseq_expr->statement_,
            new MoveStatement(
                source_expr,
                new MemExpression(
                    eseq_expr->expression_
                )
            )
        );
        tos_value_.statement_ = result_stmt;
        return;
      }
      Temporary T;
      SeqStatement* result_stmt = new SeqStatement(
          new MoveStatement(
              source_expr,
              new TempExpression(T)
          ),
          new SeqStatement(
              eseq_expr->statement_,
              new MoveStatement(
                  new TempExpression(T),
                  new MemExpression(
                      eseq_expr->expression_
                  )
              )
          )
      );
      tos_value_.statement_ = result_stmt;
      return;
    }
  }

  if (source_expr->GetNodeType() == IRT::NodeType::ESEQ &&
      target_expr->GetNodeType() == IRT::NodeType::TEMP) { //// 4(ESEQ + TEMP)
    EseqExpression* eseq_expr = dynamic_cast<EseqExpression*>(source_expr);
    TempExpression* temp_expr = dynamic_cast<TempExpression*>(target_expr);
    SeqStatement* result_stmt = new SeqStatement(
        eseq_expr->statement_,
        new MoveStatement(
            eseq_expr->expression_,
            new TempExpression(
                temp_expr->temporary_
            )
        )
    );
    tos_value_.statement_ = result_stmt;
    return;
  }

  tos_value_.statement_ = new MoveStatement(source_expr, target_expr); //// 5(other)
}

void IRT::EseqEliminateVisitor::Visit(SeqStatement* seq_statement) { //// OK
  IrtStorage elements_first = Accept(seq_statement->first_statement_);
  IrtStorage elements_second = Accept(seq_statement->second_statement_);
  SeqStatement* result_stmt = new SeqStatement(
      elements_first.statement_,
      elements_second.statement_
  );
  tos_value_.statement_ = result_stmt;
}

void IRT::EseqEliminateVisitor::Visit(LabelStatement* label_statement) { //// OK
  Statement* result_stmt = new LabelStatement(label_statement->label_);
  tos_value_.statement_ = result_stmt;
}

void IRT::EseqEliminateVisitor::Visit(BinopExpression* binop_expression) { //// OK
  IrtStorage elements_first = Accept(binop_expression->first_);
  IrtStorage elements_second = Accept(binop_expression->second_);
  Expression* first_expr = elements_first.expression_;
  Expression* second_expr = elements_second.expression_;

  if (first_expr->GetNodeType() == IRT::NodeType::ESEQ &&
      second_expr->GetNodeType() == IRT::NodeType::ESEQ) { //// BOTH ESEQ
    EseqExpression* first_eseq = dynamic_cast<EseqExpression*>(first_expr);
    EseqExpression* second_eseq = dynamic_cast<EseqExpression*>(second_expr);

    if (IsConst(first_eseq->expression_) || IsConst(second_eseq->expression_)) {
      EseqExpression* result_expr = new EseqExpression(
          new SeqStatement(
              first_eseq->statement_,
              second_eseq->statement_
          ),
          new BinopExpression(
              binop_expression->operator_type_,
              first_eseq->expression_,
              second_eseq->expression_
          )
      );
      tos_value_.expression_ = result_expr;
      return;
    }
    Temporary T;
    EseqExpression* result_expr = new EseqExpression(
        new SeqStatement(
            first_eseq->statement_,
            new SeqStatement(
                new MoveStatement(
                    first_eseq->expression_,
                    new TempExpression(T)
                ),
                second_eseq->statement_
            )
        ),
        new BinopExpression(
            binop_expression->operator_type_,
            new TempExpression(T),
            second_eseq->expression_
        )
    );
    tos_value_.expression_ = result_expr;
    return;
  }

  if (first_expr->GetNodeType() == IRT::NodeType::ESEQ) { //// Only first ESEQ
    EseqExpression* first_eseq = dynamic_cast<EseqExpression*>(first_expr);
    EseqExpression* result_expr = new EseqExpression(
        first_eseq->statement_,
        new BinopExpression(
            binop_expression->operator_type_,
            first_eseq->expression_,
            second_expr
        )
    );
    tos_value_.expression_ = result_expr;
    return;
  }

  if (second_expr->GetNodeType() == IRT::NodeType::ESEQ) { //// Only second ESEQ
    EseqExpression* second_eseq = dynamic_cast<EseqExpression*>(second_expr);
    Temporary T;
    EseqExpression* result_expr = new EseqExpression(
        new MoveStatement(
            first_expr,
            new TempExpression(T)
        ), new EseqExpression(
            second_eseq->statement_,
            new BinopExpression(
                binop_expression->operator_type_,
                new TempExpression(T),
                second_eseq->expression_
            )
        )
    );
    tos_value_.expression_ = result_expr;
    return;
  }

  BinopExpression* result_expr = new BinopExpression(
      binop_expression->operator_type_,
      first_expr,
      second_expr
  );
  tos_value_.expression_ = result_expr;
}

void IRT::EseqEliminateVisitor::Visit(TempExpression* temp_expression) { //// OK
  TempExpression* result_expr = new TempExpression(temp_expression->temporary_);
  tos_value_.expression_ = result_expr;
}

void IRT::EseqEliminateVisitor::Visit(MemExpression* mem_expression) { //// OK
  IrtStorage elements = Accept(mem_expression->expression_);
  Expression* expr = elements.expression_;

  if (expr->GetNodeType() == IRT::NodeType::ESEQ) {
    EseqExpression* eseq_expr = dynamic_cast<EseqExpression*>(expr);
    EseqExpression* result_expr = new EseqExpression(
        eseq_expr->statement_,
        new MemExpression(
            eseq_expr->expression_
        )
    );
    tos_value_.expression_ = result_expr;
    return;
  }
  MemExpression* result_expr = new MemExpression(expr);
  tos_value_.expression_ = result_expr;
}

void IRT::EseqEliminateVisitor::Visit(JumpStatement* jump_statement) { //// OK
  JumpStatement* result_stmt = new JumpStatement(jump_statement->label_);
  tos_value_.statement_ = result_stmt;
}

void IRT::EseqEliminateVisitor::Visit(CallExpression* call_expression) { //// OK
  IrtStorage expr_elements = Accept(call_expression->function_name_);
  IrtStorage list_elements = Accept(call_expression->args_);
  CallExpression* result_expr = new CallExpression(
      expr_elements.expression_,
      list_elements.expression_list_
  );
  tos_value_.expression_ = result_expr;
}

void IRT::EseqEliminateVisitor::Visit(ExpressionList* expression_list) { //// OK
  ExpressionList* result_list = new ExpressionList();

  for (auto& expression : expression_list->expressions_) {
    result_list->Add(Accept(expression).expression_);
  }
  tos_value_.expression_list_ = result_list;
}

void IRT::EseqEliminateVisitor::Visit(NameExpression* name_expression) { //// OK
  tos_value_.expression_ = new NameExpression(name_expression->label_);
}

void IRT::EseqEliminateVisitor::Visit(EseqExpression* eseq_expression) {
  IrtStorage elements_stmt = Accept(eseq_expression->statement_);
  IrtStorage elements_expr = Accept(eseq_expression->expression_);
  Statement* statement = elements_stmt.statement_;
  Expression* expression = elements_expr.expression_;

  if (expression->GetNodeType() == IRT::NodeType::ESEQ) {
    EseqExpression* eseq = dynamic_cast<EseqExpression*>(expression);
    EseqExpression* result_expr = new EseqExpression(
        new SeqStatement(
            statement,
            eseq->statement_
        ),
        expression
    );
    tos_value_.expression_ = result_expr;
  } else {
    EseqExpression* result_expr = new EseqExpression(
        statement,
        expression
    );
    tos_value_.expression_ = result_expr;
  }
}

void IRT::EseqEliminateVisitor::Visit(ExpStatement* exp_stmt) { //// OK
  IrtStorage elements = Accept(exp_stmt->GetExpression());
  auto expression = elements.expression_;

  //// Check for CALL
  if (IRT::NodeType::CALL == expression->GetNodeType()) {
    auto call_expr = dynamic_cast<CallExpression*>(expression);
    auto ir_list = ShiftEseq(call_expr->args_);
    /// ESEQ or not ESEQ
    if (call_expr->function_name_->GetNodeType() == IRT::NodeType::ESEQ) {
      IRT::EseqExpression* eseq_expr = dynamic_cast<EseqExpression*>(call_expr->function_name_);

      ExpStatement* tmp_exp_stmt = new ExpStatement(
          new CallExpression(
              eseq_expr->expression_,
              ir_list.exp_list
          )
      );
      SeqStatement* result_stmt = new SeqStatement(
          eseq_expr->statement_,
          new SeqStatement(
              ir_list.suffix,
              tmp_exp_stmt
          )
      );
      tos_value_.statement_ = result_stmt;
    } else {
      ExpStatement* tmp_exp_stmt = new ExpStatement(
          new CallExpression(
              call_expr->function_name_,
              ir_list.exp_list
          )
      );
      SeqStatement* result_stmt = new SeqStatement(
          ir_list.suffix,
          tmp_exp_stmt
      );
      tos_value_.statement_ = result_stmt;
    }
    return;
  }

  //// Check for ESEQ
  if (IRT::NodeType::ESEQ == expression->GetNodeType()) {
    IRT::EseqExpression* eseq_expr = dynamic_cast<EseqExpression*>(expression);
    tos_value_.statement_ = eseq_expr->statement_;
    return;
  }

  //// Other cases (just return ExpStatement)
  tos_value_.statement_ = new IRT::ExpStatement(expression);
}

//// I've tried to divide nodes to make code clearer,
//// but it's very difficult to think. That's why code below would
//// would be worse ¯\_(ツ)_/¯

void IRT::EseqEliminateVisitor::IRList::MakeStatementList() {
  suffix = statements.back();
  for (size_t i = statements.size(); i >= 0; --i) {
    suffix = new IRT::SeqStatement(statements[i], suffix);
  }
}

void IRT::EseqEliminateVisitor::IRList::AddStatement(IRT::Statement* statement) {
  statements.push_back(statement);
}

void IRT::EseqEliminateVisitor::IRList::SetStatement(Statement* statement) {
  suffix = statement;
}

IRT::Statement* IRT::EseqEliminateVisitor::GetTree() {
  return tos_value_.statement_;
}
