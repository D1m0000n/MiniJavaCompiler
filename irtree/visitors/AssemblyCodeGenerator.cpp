#include "AssemblyCodeGenerator.h"

void IRT::AssemblyCodeGenerator::Visit(IRT::ExpStatement* stmt) {
  stmt->GetExpression()->Accept(this);
}

void IRT::AssemblyCodeGenerator::Visit(IRT::ConstExpression* const_expression) {
  Temporary T;
  std::string reg = T.ToString();
  std::string const_str = std::to_string(const_expression->Value());
  IRT::MovCode* mov_code = new IRT::MovCode(
      reg,
      IRT::OpType::TEMP,
      const_str,
      IRT::OpType::CONST
  );
  op_codes_.push_back(mov_code);
  tos_value_ = {reg, IRT::OpType::TEMP};
}

void IRT::AssemblyCodeGenerator::Visit(JumpConditionalStatement* statement) {
  IRT::Expression* left_expr = statement->left_operand_;
  IRT::Expression* right_expr = statement->right_operand_;

  if (left_expr->GetNodeType() == IRT::NodeType::CONST &&
      right_expr->GetNodeType() == IRT::NodeType::CONST) {
    int left_const = dynamic_cast<ConstExpression*>(left_expr)->Value();
    int right_const = dynamic_cast<ConstExpression*>(right_expr)->Value();

    switch (statement->operator_type_) {
      case IRT::LogicOperatorType::LT: {
        if (left_const < right_const) {
          IRT::JumpCode* jump = new JumpCode(statement->label_true_.ToString());
          op_codes_.push_back(jump);
        }
        break;
      }
      case IRT::LogicOperatorType::GT: {
        if (left_const > right_const) {
          IRT::JumpCode* jump = new JumpCode(statement->label_true_.ToString());
          op_codes_.push_back(jump);
        }
        break;
      }
      case IRT::LogicOperatorType::EQ: {
        if (left_const == right_const) {
          IRT::JumpCode* jump = new JumpCode(statement->label_true_.ToString());
          op_codes_.push_back(jump);
        }
        break;
      }
      case IRT::LogicOperatorType::NE: {
        if (left_const != right_const) {
          IRT::JumpCode* jump = new JumpCode(statement->label_true_.ToString());
          op_codes_.push_back(jump);
        }
        break;
      }
    }
    return;
  }

  std::string suffix;

  switch (statement->operator_type_) {
    case IRT::LogicOperatorType::LT: {
      suffix = "lt";
      break;
    }
    case IRT::LogicOperatorType::GT: {
      suffix = "gt";
      break;
    }
    case IRT::LogicOperatorType::EQ: {
      suffix = "eq";
      break;
    }
    case IRT::LogicOperatorType::NE: {
      suffix = "ne";
      break;
    }
  }

  if (left_expr->GetNodeType() == IRT::NodeType::CONST) {
    int left_const = dynamic_cast<ConstExpression*>(left_expr)->Value();
    auto reg_name = Accept(right_expr);
    Temporary T;
    IRT::MovCode* mov = new MovCode(T.ToString(), IRT::OpType::TEMP, std::to_string(left_const), IRT::OpType::CONST);
    op_codes_.push_back(mov);
    IRT::CmpCode* cmp = new CmpCode(T.ToString(), OpType::TEMP, reg_name.first, reg_name.second);
    op_codes_.push_back(cmp);
  }

  if (right_expr->GetNodeType() == IRT::NodeType::CONST) {
    int right_const = dynamic_cast<ConstExpression*>(right_expr)->Value();
    auto reg_name = Accept(left_expr);
    IRT::CmpCode* mov = new CmpCode(reg_name.first, reg_name.second, std::to_string(right_const), OpType::CONST);
    op_codes_.push_back(mov);
  }

  if (left_expr->GetNodeType() != NodeType::CONST &&
      right_expr->GetNodeType() != NodeType::CONST) {
    auto left_reg = Accept(left_expr);
    auto right_reg = Accept(right_expr);
    CmpCode* cmp = new CmpCode(left_reg.first, left_reg.second, right_reg.first, right_reg.second);
    op_codes_.push_back(cmp);
  }

  JumpCode* jump = new JumpCode(statement->label_true_.ToString());
  jump->SetSuffix(suffix);
  op_codes_.push_back(jump);
}

void IRT::AssemblyCodeGenerator::Visit(IRT::MoveStatement* statement) {
  bool return_value = false;
  if (statement->source_->GetNodeType() == IRT::NodeType::TEMP) {
    TempExpression* temp = dynamic_cast<TempExpression*>(statement->source_);
    if (temp->temporary_.ToString() == "::return_value") {
      return_value = true;
    }
  }

  if (statement->target_->GetNodeType() == IRT::NodeType::MEM) {
    auto src = Accept(statement->source_);
    MemExpression* mem_expr = dynamic_cast<MemExpression*>(statement->target_);
    switch (mem_expr->expression_->GetNodeType()) {
      case IRT::NodeType::BINOP: {
        BinopExpression* binop_expr = dynamic_cast<BinopExpression*>(mem_expr->expression_);
        if (binop_expr->operator_type_ == BinaryOperatorType::PLUS) {
          if (binop_expr->first_->GetNodeType() == IRT::NodeType::CONST ||
              binop_expr->second_->GetNodeType() == IRT::NodeType::CONST) {
            IRT::Expression* accept_node = binop_expr->first_;
            IRT::Expression* const_node = binop_expr->second_;
            if (accept_node->GetNodeType() == IRT::NodeType::CONST) {
              std::swap(accept_node, const_node);
            }
            auto accept_result = Accept(accept_node);
            int shift = dynamic_cast<ConstExpression*>(const_node)->Value();
            StrCode* str = new StrCode(
                src.first,
                src.second,
                accept_result.first,
                accept_result.second,
                shift
            );
            op_codes_.push_back(str);
            break;
          }
        } else {
          throw std::runtime_error("hzhz, smth went wrong");
        }
      }
      case IRT::NodeType::CONST: {
        ConstExpression* const_expr = dynamic_cast<ConstExpression*>(mem_expr->expression_);
        StrCode* str = new StrCode(
            src.first,
            src.second,
            "",
            IRT::OpType::NONE,
            const_expr->Value()
        );
        op_codes_.push_back(str);
        break;
      }
      default: {
        auto target = Accept(mem_expr->expression_);
        StrCode* str = new StrCode(
            src.first,
            src.second,
            target.first,
            target.second,
            0
        );
        op_codes_.push_back(str);
      }
    }
  } else {
    auto reg_src = Accept(statement->source_);
    auto reg_trg = Accept(statement->target_);
    MovCode* mov = new MovCode(reg_trg.first, reg_trg.second, reg_src.first, reg_src.second);
    op_codes_.push_back(mov);
  }

  if (return_value) {
    JumpCode* jump = new JumpCode("lr");
    jump->SetSuffix("x");
    op_codes_.push_back(jump);
  }
}

void IRT::AssemblyCodeGenerator::Visit(IRT::SeqStatement* statement) {}

void IRT::AssemblyCodeGenerator::Visit(IRT::LabelStatement* statement) {
  LabelCode* label = new LabelCode(statement->label_.ToString());
  op_codes_.push_back(label);
}

int IRT::AssemblyCodeGenerator::CountConst(int first, int second, IRT::BinaryOperatorType operator_type) {
  switch (operator_type) {
    case IRT::BinaryOperatorType::PLUS:return first + second;
    case IRT::BinaryOperatorType::MINUS:return first - second;
    case IRT::BinaryOperatorType::MUL:return first * second;
    case IRT::BinaryOperatorType::DIV:return first / second;
    case IRT::BinaryOperatorType::MOD:return first % second;
    case IRT::BinaryOperatorType::AND:return (first && second);
    case IRT::BinaryOperatorType::OR:return (first || second);
  }
}

void IRT::AssemblyCodeGenerator::Visit(IRT::BinopExpression* expression) {
  Expression* first = expression->first_;
  Expression* second = expression->second_;
  if (first->GetNodeType() == IRT::NodeType::CONST &&
      second->GetNodeType() == IRT::NodeType::CONST) {
    int const_first = dynamic_cast<ConstExpression*>(first)->Value();
    int const_second = dynamic_cast<ConstExpression*>(second)->Value();
    Temporary T;
    int result_const = CountConst(const_first, const_second, expression->operator_type_);
    auto mov = new MovCode(T.ToString(), OpType::TEMP, std::to_string(result_const), OpType::CONST);
    op_codes_.push_back(mov);
    tos_value_ = {T.ToString(), IRT::OpType::TEMP};
    return;
  }

  if (first->GetNodeType() == IRT::NodeType::CONST) {
    auto reg_name = Accept(second);
    int val = dynamic_cast<ConstExpression*>(first)->Value();
    Temporary T;
    MakeBinOperation(T.ToString(), IRT::OpType::TEMP, reg_name.first, reg_name.second,
                     std::to_string(val), IRT::OpType::CONST, expression->operator_type_);
    tos_value_ = {T.ToString(), IRT::OpType::TEMP};
    return;
  }

  if (second->GetNodeType() == IRT::NodeType::CONST) {
    auto reg_name = Accept(first);
    int val = dynamic_cast<ConstExpression*>(second)->Value();
    MakeBinOperation(reg_name.first, reg_name.second, reg_name.first, reg_name.second,
                     std::to_string(val), IRT::OpType::CONST, expression->operator_type_);
    tos_value_ = reg_name;
    return;
  } else {
    auto reg_fi = Accept(first);
    auto reg_se = Accept(second);
    MakeBinOperation(reg_fi.first,
                     reg_fi.second,
                     reg_fi.first,
                     reg_fi.second,
                     reg_se.first,
                     reg_se.second,
                     expression->operator_type_);
    tos_value_ = reg_fi;
    return;
  }
}

void IRT::AssemblyCodeGenerator::Visit(IRT::TempExpression* expression) {
  std::string out_str = expression->temporary_.ToString();
  size_t found = out_str.find("::fp");
  if (found != std::string::npos) {
    tos_value_ = {out_str, OpType::FP};
  } else {
    tos_value_ = {out_str, OpType::TEMP};
  }
}

void IRT::AssemblyCodeGenerator::Visit(IRT::MemExpression* expression) {
  Temporary T;
  Expression* expr = expression->expression_;
  if (expr->GetNodeType() == IRT::NodeType::CONST) {
    int const_val = dynamic_cast<ConstExpression*>(expr)->Value();
    auto ldr = new LdrCode(T.ToString(), IRT::OpType::TEMP, "", IRT::OpType::NONE, const_val);
    op_codes_.push_back(ldr);
    tos_value_ = {T.ToString(), IRT::OpType::TEMP};
    return;
  }

  if (expr->GetNodeType() != IRT::NodeType::BINOP) {
    auto reg = Accept(expr);
    auto ldr = new LdrCode(T.ToString(), IRT::OpType::TEMP, reg.first, reg.second, 0);
    op_codes_.push_back(ldr);
    tos_value_ = {T.ToString(), OpType::TEMP};
    return;
  }

  auto binop_expr = dynamic_cast<BinopExpression*>(expr);

  if (binop_expr->operator_type_ != BinaryOperatorType::PLUS ||
      ((binop_expr->first_->GetNodeType() == NodeType::CONST) ==
          (binop_expr->second_->GetNodeType() == NodeType::CONST))) {
    auto reg = Accept(expr);
    auto ldr = new LdrCode(T.ToString(), IRT::OpType::TEMP, reg.first, reg.second, 0);
    op_codes_.push_back(ldr);
    tos_value_ = {T.ToString(), OpType::TEMP};
    return;
  }

  if (binop_expr->first_->GetNodeType() == NodeType::CONST) {
    int shift = dynamic_cast<ConstExpression*>(binop_expr->first_)->Value();
    auto reg = Accept(binop_expr->second_);
    auto ldr = new LdrCode(T.ToString(), OpType::TEMP, reg.first, reg.second, shift);
    op_codes_.push_back(ldr);
    tos_value_ = {T.ToString(), OpType::TEMP};
    return;
  }

  auto reg = Accept(binop_expr->first_);
  int offset = dynamic_cast<ConstExpression*>(binop_expr->second_)->Value();
  auto ldr = new LdrCode(T.ToString(), OpType::TEMP, reg.first, reg.second, offset);
  op_codes_.push_back(ldr);
  tos_value_ = {T.ToString(), OpType::TEMP};
}

void IRT::AssemblyCodeGenerator::Visit(JumpStatement* statement) {
  auto jump = new JumpCode(statement->label_.ToString());
  op_codes_.push_back(jump);
}

void IRT::AssemblyCodeGenerator::Visit(CallExpression* call_expression) {
  std::vector<std::pair<std::string, OpType>> args;
  for (size_t i = call_expression->args_->expressions_.size() - 1; i > 3; --i) {
    auto reg = Accept(call_expression->args_->expressions_[i]);
    args.push_back(reg);
    auto push = new PushCode(reg.first, reg.second);
    op_codes_.push_back(push);
  }
  int beg_ind;
  if (call_expression->args_->expressions_.size() >= 4) {
    beg_ind = 3;
  } else {
    beg_ind = call_expression->args_->expressions_.size() - 1;
  }
  for (int i = beg_ind; i >= 0; --i) {
    auto reg = Accept(call_expression->args_->expressions_[i]);
    auto mov = new MovCode("r" + std::to_string(i), OpType::REG, reg.first, reg.second);
    op_codes_.push_back(mov);
  }
  auto func_name = Accept(call_expression->function_name_);
  auto call = new JumpCode(func_name.first);
  call->SetSuffix("l");
  op_codes_.push_back(call);
  Temporary T;
  auto mov = new MovCode(T.ToString(), OpType::TEMP, "r0", OpType::REG);
  op_codes_.push_back(mov);
  std::reverse(args.begin(), args.end());
  for (auto arg_name : args) {
    auto pop = new PopCode(arg_name.first, arg_name.second);
    op_codes_.push_back(pop);
  }
  tos_value_ = {T.ToString(), OpType::TEMP};
}

void IRT::AssemblyCodeGenerator::Visit(ExpressionList* expression_list) {}

void IRT::AssemblyCodeGenerator::Visit(NameExpression* expression) {
  tos_value_ = {expression->label_.ToString(), OpType::NAME};
}

void IRT::AssemblyCodeGenerator::Visit(EseqExpression* eseq) {}

void IRT::AssemblyCodeGenerator::Visit(PrintStatement* statement) {
  auto reg = Accept(statement->expression_);
  auto mov = new MovCode("r0", OpType::REG, reg.first, reg.second);
  op_codes_.push_back(mov);
  auto jump = new JumpCode("print");
  jump->SetSuffix("l");
  op_codes_.push_back(jump);
}

void IRT::AssemblyCodeGenerator::MakeBinOperation(std::string regd,
                                                  IRT::OpType regd_tp,
                                                  std::string rega,
                                                  IRT::OpType rega_tp,
                                                  std::string argb,
                                                  IRT::OpType argb_tp,
                                                  IRT::BinaryOperatorType operator_type) {
  switch (operator_type) {
    case IRT::BinaryOperatorType::PLUS: {
      auto add = new AddCode(regd, regd_tp, rega, rega_tp, argb, argb_tp);
      op_codes_.push_back(add);
      break;
    }
    case BinaryOperatorType::MINUS: {
      auto sub = new SubCode(regd, regd_tp, rega, rega_tp, argb, argb_tp);
      op_codes_.push_back(sub);
      break;
    }
    case BinaryOperatorType::MUL: {
      auto mul = new MulCode(regd, regd_tp, rega, rega_tp, argb, argb_tp);
      op_codes_.push_back(mul);
      break;
    }
    case BinaryOperatorType::DIV: {
      auto div = new DivCode(regd, regd_tp, rega, rega_tp, argb, argb_tp);
      op_codes_.push_back(div);
      break;
    }
    case BinaryOperatorType::MOD: {
      Temporary T1;
      auto add = new AddCode(T1.ToString(), IRT::OpType::TEMP, rega, rega_tp, argb, argb_tp);
      Temporary T2;
      auto sub = new SubCode(T2.ToString(), IRT::OpType::TEMP, argb, argb_tp, "1", IRT::OpType::CONST);
      auto andop = new AndCode(regd, regd_tp, T1.ToString(), IRT::OpType::TEMP, T2.ToString(), IRT::OpType::TEMP);
      op_codes_.push_back(add);
      op_codes_.push_back(sub);
      op_codes_.push_back(andop);
      break;
    }
    case BinaryOperatorType::AND: {
      auto andop = new AndCode(regd, regd_tp, rega, rega_tp, argb, argb_tp);
      op_codes_.push_back(andop);
      break;
    }
    case BinaryOperatorType::OR: {
      auto orop = new OrCode(regd, regd_tp, rega, rega_tp, argb, argb_tp);
      op_codes_.push_back(orop);
      break;
    }
  }
}

std::vector<IRT::OpCode*> IRT::AssemblyCodeGenerator::GetCodes() {
  return op_codes_;
}

void IRT::AssemblyCodeGenerator::PushRegisters(std::vector<int> regs) {
  auto push_list = new PushListCode(regs);
  op_codes_.push_back(push_list);
}

void IRT::AssemblyCodeGenerator::PopRegisters(std::vector<int> regs) {
  auto pop_list = new PopListCode(regs);
  op_codes_.push_back(pop_list);
}

void IRT::AssemblyCodeGenerator::MakeBasePointer() {
  auto push = new PushCode("r11", OpType::REG);
  auto mov = new MovCode("r11", OpType::REG, "sp", OpType::REG);
  op_codes_.push_back(push);
  op_codes_.push_back(mov);
}

void IRT::AssemblyCodeGenerator::EraseBasePointer() {
  auto pop = new PopCode("r11", OpType::REG);
  op_codes_.push_back(pop);
}
