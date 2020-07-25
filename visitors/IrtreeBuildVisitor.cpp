#include <irtree/tree_wrapper/ExpressionWrapper.h>
#include <irtree/nodes/expressions/ConstExpression.h>
#include <expressions/NumberExpression.h>
#include <irtree/tree_wrapper/conditional_wrappers/NegateConditionalWrapper.h>
#include <irtree/tree_wrapper/conditional_wrappers/AndConditionalWrapper.h>
#include <expressions/AndExpression.h>
#include <expressions/OrExpression.h>
#include <irtree/tree_wrapper/conditional_wrappers/OrConditionalWrapper.h>
#include <statements/Assignment.h>
#include <irtree/types/BinaryOperatorType.h>
#include <irtree/generators/Temporary.h>
#include <irtree/nodes/expressions/BinopExpression.h>
#include <irtree/nodes/expressions/TempExpression.h>
#include <irtree/nodes/expressions/MemExpression.h>
#include <irtree/nodes/statements/MoveStatement.h>
#include <irtree/tree_wrapper/StatementWrapper.h>
#include <irtree/nodes/statements/LabelStatement.h>
#include <irtree/nodes/statements/SeqStatement.h>
#include <irtree/nodes/statements/JumpStatement.h>
#include <irtree/nodes/ExpressionList.h>
#include <irtree/nodes/expressions/CallExpression.h>
#include <irtree/nodes/expressions/NameExpression.h>
#include <irtree/types/LogicOperatorType.h>
#include <irtree/tree_wrapper/conditional_wrappers/RelativeConditionalWrapper.h>
#include <elements.h>

#include <IrtreeBuildVisitor.h>

void IrtreeBuildVisitor::Visit(NumberExpression* expression) {
  tos_value_ = new IRT::ExpressionWrapper(
      new IRT::ConstExpression(expression->value_)
  );
}

void IrtreeBuildVisitor::Visit(AddExpression* expression) {
  auto lhs = Accept(expression->first);
  auto rhs = Accept(expression->second);

  tos_value_ = new IRT::ExpressionWrapper(
      new IRT::BinopExpression(
          IRT::BinaryOperatorType::PLUS,
          lhs->ToExpression(),
          rhs->ToExpression()
      )
  );
}

void IrtreeBuildVisitor::Visit(SubtractExpression* expression) {
  auto lhs = Accept(expression->first);
  auto rhs = Accept(expression->second);

  tos_value_ = new IRT::ExpressionWrapper(
      new IRT::BinopExpression(
          IRT::BinaryOperatorType::MINUS,
          lhs->ToExpression(),
          rhs->ToExpression()
      )
  );
}
void IrtreeBuildVisitor::Visit(MulExpression* expression) {
  auto lhs = Accept(expression->first);
  auto rhs = Accept(expression->second);

  tos_value_ = new IRT::ExpressionWrapper(
      new IRT::BinopExpression(
          IRT::BinaryOperatorType::MUL,
          lhs->ToExpression(),
          rhs->ToExpression()
      )
  );
}

void IrtreeBuildVisitor::Visit(DivExpression* expression) {
  auto lhs = Accept(expression->first);
  auto rhs = Accept(expression->second);

  tos_value_ = new IRT::ExpressionWrapper(
      new IRT::BinopExpression(
          IRT::BinaryOperatorType::DIV,
          lhs->ToExpression(),
          rhs->ToExpression()
      )
  );
}

void IrtreeBuildVisitor::Visit(ModuloExpression* expression) {
  auto lhs = Accept(expression->first);
  auto rhs = Accept(expression->second);

  tos_value_ = new IRT::ExpressionWrapper(
      new IRT::BinopExpression(
          IRT::BinaryOperatorType::MOD,
          lhs->ToExpression(),
          rhs->ToExpression()
      )
  );
}

void IrtreeBuildVisitor::Visit(IdentExpression* expression) {
  auto address = current_frame_->GetAddress(expression->ident_);

  tos_value_ = new IRT::ExpressionWrapper(address->ToExpression());
}

void IrtreeBuildVisitor::Visit(Assignment* assignment) {
  auto rvalue = current_frame_->GetAddress(
      assignment->variable_
  )->ToExpression();
  auto source = Accept(assignment->expression_)->ToExpression();

  tos_value_ = new IRT::StatementWrapper(new IRT::MoveStatement(
      source,
      rvalue
      )
  );
}

void IrtreeBuildVisitor::Visit(VarDecl* var_decl) {
  current_frame_->AddLocalVariable(var_decl->variable_);
  tos_value_ = nullptr;
}

void IrtreeBuildVisitor::Visit(PrintStatement* statement) {
  tos_value_ = nullptr;
}

void IrtreeBuildVisitor::Visit(AssignmentList* assignment_list) {
  if (assignment_list->statements_.empty()) {
    tos_value_ = nullptr;
    return;
  }

  if (assignment_list->statements_.size() == 1) {
    tos_value_ = Accept(assignment_list->statements_[0]);
  } else {
    std::vector<IRT::Statement*> statements;
    statements.reserve(assignment_list->statements_.size());
//    size_t index = 0;
    for (auto statement: assignment_list->statements_) {
      auto stmt = Accept(statement);
      if (stmt) {
        statements.push_back(stmt->ToStatement());
      }
    }
    IRT::Statement* suffix = statements.back();

    for (int index = static_cast<int>(statements.size()) - 2; index >= 0; --index) {
      suffix = new IRT::SeqStatement(
          statements.at(index),
          suffix
      );
    }
    tos_value_ = new IRT::StatementWrapper(suffix);
  }
}

void IrtreeBuildVisitor::Visit(ScopeAssignmentList* list) {
  current_frame_->SetupScope();

  tos_value_ = Accept(list->statement_list);
  current_frame_->TearDownScope();
}

void IrtreeBuildVisitor::Visit(Program* program) {
  program->main_class_->Accept(this);
  program->class_declarations_->Accept(this);
}

void IrtreeBuildVisitor::Visit(ParamList* param_list) {
  for (auto param: param_list->params_) {
    current_frame_->AddArgumentAddress(param);
  }

}
void IrtreeBuildVisitor::Visit(Function* function) {
  // build new frame
  current_frame_ = new IRT::FrameTranslator(function->name_);
  std::string full_func_name = this_ + "::" + function->name_;
  frame_translator_[full_func_name] = current_frame_;

  function->param_list_->Accept(this);

  current_frame_->AddReturnAddress();

  auto statements_ir = Accept(function->statements_);

  if (statements_ir) {

    tos_value_ = new IRT::StatementWrapper(
        new IRT::SeqStatement(
            new IRT::LabelStatement(IRT::Label(full_func_name)),
            statements_ir->ToStatement()
        )
    );
  }
//  else {
//    // generating return 0
//    tos_value_ = new IRT::StatementWrapper(
//        new IRT::SeqStatement(
//            new IRT::LabelStatement(IRT::Label(function->name_)),
//            new IRT::MoveStatement(
//                current_frame_->GetReturnValueAddress()->ToExpression(),
//                new IRT::ConstExpression(0)
//            )
//        )
//    );
//  }
  method_trees_.emplace(function->name_, tos_value_->ToStatement());
}
void IrtreeBuildVisitor::Visit(FunctionCallExpression* statement) {
  IRT::ExpressionList* irt_expressions = new IRT::ExpressionList();

  for (auto it: statement->param_list_->params_) {
    irt_expressions->Add(Accept(it)->ToExpression());
  }

  tos_value_ = new IRT::ExpressionWrapper(
      new IRT::CallExpression(
          new IRT::NameExpression(IRT::Label(statement->name_)),
          irt_expressions
      )
  );

}
void IrtreeBuildVisitor::Visit(FunctionList* function_list) {
  for (auto function: function_list->functions_) {
    function->Accept(this);
  }

}
void IrtreeBuildVisitor::Visit(ParamValueList* value_list) {

}
void IrtreeBuildVisitor::Visit(ReturnStatement* return_statement) {
  auto return_expr = Accept(return_statement->return_expression_);
  tos_value_ = new IRT::StatementWrapper(
      new IRT::MoveStatement(
          current_frame_->GetReturnValueAddress()->ToExpression(),
          return_expr->ToExpression()
      )
  );
}

void IrtreeBuildVisitor::Visit(AndExpression* and_expression) {
  auto first_wrapper = Accept(and_expression->first);
  auto second_wrapper = Accept(and_expression->second);

  tos_value_ = new IRT::AndConditionalWrapper(
      first_wrapper,
      second_wrapper
  );
}

void IrtreeBuildVisitor::Visit(OrExpression* or_expression) {
  auto first_wrapper = Accept(or_expression->first);
  auto second_wrapper = Accept(or_expression->second);

  tos_value_ = new IRT::OrConditionalWrapper(
      first_wrapper,
      second_wrapper
  );
}

void IrtreeBuildVisitor::Visit(IfStatement* if_statement) {
  auto if_cond_expression = Accept(if_statement->expression_);
  current_frame_->SetupScope();
  auto true_stmt = Accept(if_statement->true_statement_);
  current_frame_->TearDownScope();
  current_frame_->SetupScope();
  IRT::SubtreeWrapper* false_stmt;
  if (if_statement->false_statement_) {
    false_stmt = Accept(if_statement->false_statement_);
  } else {
    false_stmt = nullptr;
  }
  current_frame_->TearDownScope();

  IRT::Label label_true;
  IRT::Label label_false;
  IRT::Label label_join;

  IRT::Statement* suffix = new IRT::LabelStatement(label_join);

  IRT::Label* result_true = &label_join;
  IRT::Label* result_false = &label_join;

  if (false_stmt) {
    result_false = &label_false;
    suffix = new IRT::SeqStatement(
        new IRT::LabelStatement(label_false),
        new IRT::SeqStatement(false_stmt->ToStatement(), suffix)
    );

    if (true_stmt) {
      suffix = new IRT::SeqStatement(
          new IRT::JumpStatement(label_join),
          suffix
      );
    }
  }

  if (true_stmt) {
    result_true = &label_true;
    suffix = new IRT::SeqStatement(
        new IRT::LabelStatement(label_true),
        new IRT::SeqStatement(true_stmt->ToStatement(), suffix)
    );
  }

  tos_value_ = new IRT::StatementWrapper(
      new IRT::SeqStatement(
          if_cond_expression->ToConditional(*result_true, *result_false),
          suffix
      )
  );

}

void IrtreeBuildVisitor::Visit(WhileStatement* while_statement) {
  auto while_expression = Accept(while_statement->expression_);
  current_frame_->SetupScope();
  auto while_stmt = Accept(while_statement->statement_);
  current_frame_->TearDownScope();

  IRT::Label label_begin;
  IRT::Label label_test;
  IRT::Label label_done;

  IRT::Statement* suffix = new IRT::LabelStatement(label_done);

  if (while_stmt) {
    suffix = new IRT::SeqStatement(
        while_stmt->ToStatement(),
        new IRT::SeqStatement(
            new IRT::JumpStatement(label_test),
            suffix
        )
    );
  }

  tos_value_ = new IRT::StatementWrapper(
      new IRT::SeqStatement(
          new IRT::LabelStatement(label_test),
          new IRT::SeqStatement(
              while_expression->ToConditional(label_begin, label_done),
              new IRT::SeqStatement(
                  new IRT::LabelStatement(label_begin),
                  suffix
              )
          )
      )
  );
}

void IrtreeBuildVisitor::Visit(IsGreaterExpression* gt_expression) {
  tos_value_ = new IRT::RelativeConditionalWrapper(
      IRT::LogicOperatorType::GT,
      Accept(gt_expression->first)->ToExpression(),
      Accept(gt_expression->second)->ToExpression()
  );
}
void IrtreeBuildVisitor::Visit(IsLessExpression* lt_expression) {
  tos_value_ = new IRT::RelativeConditionalWrapper(
      IRT::LogicOperatorType::LT,
      Accept(lt_expression->first)->ToExpression(),
      Accept(lt_expression->second)->ToExpression()
  );
}

void IrtreeBuildVisitor::Visit(IsEqualExpression* eq_expression) {
  tos_value_ = new IRT::RelativeConditionalWrapper(
      IRT::LogicOperatorType::EQ,
      Accept(eq_expression->first)->ToExpression(),
      Accept(eq_expression->second)->ToExpression()
  );
}

void IrtreeBuildVisitor::Visit(DeclarationList* declaration_list) {
  for (auto declaration : declaration_list->declarations_) {
    tos_value_ = Accept(declaration);
  }
}

void IrtreeBuildVisitor::Visit(ThisExpression* this_expression) {
}

void IrtreeBuildVisitor::Visit(MainClass* main_class) {
  this_ = main_class->identifier;
//  main_class->statements_->Accept(this);
  main_function_->Accept(this);
}

void IrtreeBuildVisitor::Visit(ClassDecl* class_decl) {
  this_ = class_decl->identifier;
  class_decl->declaration_list_->Accept(this);
}

void IrtreeBuildVisitor::Visit(MethodDecl* method_decl) {
  //// to be honest, this class is unused,
  //// but Im 2 lazy 2 delete it ¯\_(ツ)_/¯
  //// that's why Im continue fake work on it)
}

IrtreeBuildVisitor::IrtreeBuildVisitor(ScopeLayerTree* layer_tree) : tree_(layer_tree) {
  // We don't need symbol table but you need with type system
  // Our functions return one type and operate with one type
}

IrtMapping IrtreeBuildVisitor::GetTrees() {
  return method_trees_;
}

void IrtreeBuildVisitor::SetMainFunction(Function* main_func) {
  main_function_ = main_func;
}
