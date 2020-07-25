#pragma once

#include "include/driver.hh"
#include "parser.hh"

#include "visitors/Interpreter.h"
#include "visitors/PrintVisitor.h"
#include "visitors/SymbolTreeVisitor.h"
#include "visitors/TypeCheckerVisitor.h"
#include "visitors/FunctionCallVisitor.h"
#include <visitors/IrtreeBuildVisitor.h>

#include <function-mechanisms/FunctionStorage.h>

#include <irtree/visitors/PrintVisitor.h>
#include <irtree/visitors/DoubleCallEliminateVisitor.h>
#include <irtree/visitors/EseqEliminateVisitor.h>
#include <irtree/visitors/LinearizeVisitor.h>

Driver::Driver() :
    trace_parsing(false),
    trace_scanning(false),
    scanner(*this), parser(scanner, *this) {
}

int Driver::parse(const std::string& f) {
  file = f;
  location.initialize(&file);
  scan_begin();
  parser.set_debug_level(trace_parsing);
  int res = parser();
  std::cout << "parser " << res << std::endl;
  scan_end();
  return res;
}

void Driver::Evaluate() {
  SymbolTreeVisitor visitor;
  try {
    visitor.Visit(program);
  } catch (std::runtime_error& error) {
    std::cout << error.what() << std::endl;
    exit(1);
  }
  std::cout << "Symbol tree built" << std::endl;

  ScopeLayerTree root = visitor.GetRoot();

  auto methods = visitor.GetFunctions();
  FunctionStorage& storage = FunctionStorage::GetInstance();
  for (auto it : methods) {
    storage.Set(it.first, it.second);
  }

  TypeCheckerVisitor type_checker(&root);
  try {
    type_checker.CheckTypes(program);
  } catch (std::runtime_error& error) {
    std::cout << error.what() << std::endl;
    exit(1);
  }
  std::cout << "Types checked" << std::endl;

  std::string main_func_name = program->main_class_->identifier + "." + "main";
  Function* main_function = storage.Get(Symbol(main_func_name));
  std::shared_ptr<Method> method_type = std::dynamic_pointer_cast<Method>(
      root.Get(Symbol(main_func_name))
  );

  FunctionCallVisitor function_visitor(
      root.GetFunctionScopeByName(Symbol(main_func_name)),
      method_type
  );
  function_visitor.SetTree(&root);
  function_visitor.SetThis(program->main_class_->identifier);
  function_visitor.Visit(main_function);

  std::string prefix_path = "ir_canonic_test/trash_folder/";

  root.PrintTree(prefix_path + "symbol_tree.txt");

  IrtreeBuildVisitor irt_build_visitor(&root);
  irt_build_visitor.SetMainFunction(main_function);
  irt_build_visitor.Visit(program);

  IrtMapping irt_methods = irt_build_visitor.GetTrees();

  for (auto func_view = irt_methods.begin(); func_view != irt_methods.end(); ++func_view) {
    IRT::PrintVisitor print_visitor_irt(prefix_path + func_view->first + "_irt.txt");
    irt_methods[func_view->first]->Accept(&print_visitor_irt);

    IRT::DoubleCallEliminateVisitor call_eliminate_visitor;
    irt_methods[func_view->first]->Accept(&call_eliminate_visitor);
    auto stmt_result = call_eliminate_visitor.GetTree();
    irt_methods[func_view->first] = stmt_result;


    std::string file_name = prefix_path + func_view->first + "_without_double_call.txt";
    IRT::PrintVisitor print_visitor_two(
        prefix_path + func_view->first + "_without_double_call.txt"
    );
    stmt_result->Accept(&print_visitor_two);

    IRT::EseqEliminateVisitor eseq_eliminate_visitor;
    stmt_result->Accept(&eseq_eliminate_visitor);
    stmt_result = eseq_eliminate_visitor.GetTree();
    irt_methods[func_view->first] = stmt_result;
    IRT::PrintVisitor print_visitor_three(
        prefix_path + func_view->first + "_without_ESEQ.txt"
    );
    stmt_result->Accept(&print_visitor_three);

    IRT::LinearizeVisitor linearize_visitor;
    stmt_result->Accept(&linearize_visitor);
    stmt_result = linearize_visitor.GetTree();
    irt_methods[func_view->first] = stmt_result;
    statements_sequence_[func_view->first] = MakeStatementsSequence(stmt_result);

    IRT::PrintVisitor print_visitor_four(
        prefix_path + func_view->first + "_linearized.txt"
    );
    stmt_result->Accept(&print_visitor_four);

  }

  MakeBlocks();
  PrintTraces();
//  Interpreter interpreter(root);
//  interpreter.GetResult(program);
}

void Driver::scan_begin() {
  scanner.set_debug(trace_scanning);
  if (file.empty() || file == "-") {
  } else {
    stream.open(file);
    std::cout << file << std::endl;
    scanner.yyrestart(&stream);
  }
}

void Driver::scan_end() {
  stream.close();
}

void Driver::PrintTree(const std::string& filename) {
  PrintVisitor visitor(filename);
  visitor.Visit(program);
}

void Driver::MakeBlocks() {
  for (auto func_view : statements_sequence_) {
    auto blocks = GetBlocksFromMethod(func_view.second);
    blocks.back().SetJump(
        new IRT::JumpStatement(
            IRT::Label(func_view.first + "_done")
        )
    );
    CompareLabelToBlock(blocks);
    traces_[func_view.first] = MakeTraces(blocks);
  }
}

std::vector<IRT::Statement*> Driver::MakeStatementsSequence(IRT::Statement* statement) {
  std::vector<IRT::Statement*> sequence_stmts;
  IRT::SeqStatement* current_stmt = dynamic_cast<IRT::SeqStatement*>(statement);

  while (1 > 0) {
    sequence_stmts.push_back(current_stmt->first_statement_);
    //// We doesn't check any errors, because we do it before

    IRT::Statement* save_stmt = current_stmt;
    current_stmt = dynamic_cast<IRT::SeqStatement*>(current_stmt->second_statement_);
    if (nullptr == current_stmt) {
      sequence_stmts.push_back(save_stmt);
      break;
    }
  }

  return sequence_stmts;
}

std::vector<IRT::Block> Driver::GetBlocksFromMethod(std::vector<IRT::Statement*>& statements) {
  std::vector<IRT::Block> blocks;
  blocks.emplace_back();
  for (auto& statement : statements) {
    IRT::Block& current_block = blocks.back();

    if (statement->GetNodeType() == IRT::NodeType::JUMP) {
      IRT::JumpStatement* jump_stmt = dynamic_cast<IRT::JumpStatement*>(statement);
      current_block.SetJump(jump_stmt);
      continue;
    }

    if (statement->GetNodeType() == IRT::NodeType::CJUMP) {
      IRT::JumpConditionalStatement* cjump_stmt = dynamic_cast<IRT::JumpConditionalStatement*>(statement);
      current_block.SetJump(cjump_stmt);
      continue;
    }

    if (statement->GetNodeType() == IRT::NodeType::LABEL) {
      IRT::LabelStatement* label = dynamic_cast<IRT::LabelStatement*>(statement);
      if (current_block.GetLabel() == nullptr) { //// first block
        current_block.SetLabel(label);
      } else {
        if (current_block.GetJump() == nullptr) { //// found 2 labels in a roll =)
          current_block.SetJump(
              new IRT::JumpStatement(label->label_)
          );
        }
        blocks.emplace_back();
        blocks.back().SetLabel(label);
      }
      continue;
    }

    current_block.Add(statement);
  }

  return blocks;
}

void Driver::CompareLabelToBlock(std::vector<IRT::Block>& blocks) {
  for (auto& block : blocks) {
    label_to_block_[block.GetLabel()->label_.ToString()] = &block;
  }
}

std::vector<IRT::Trace> Driver::MakeTraces(std::vector<IRT::Block>& blocks) {
  std::vector<IRT::Trace> traces;
  std::unordered_map<std::string, bool> used;
  for (auto& current_block : blocks) {
    std::string block_label = current_block.GetLabel()->label_.ToString();
    used[block_label] = false;
  }
  for (auto& current_block : blocks) {
    std::string block_label = current_block.GetLabel()->label_.ToString();
    if (used[block_label]) {
      continue;
    }
    traces.emplace_back(); //// build another trace
    auto& current_trace = traces.back();
    IRT::Block* current_trace_pointer = &current_block;
    block_label = current_trace_pointer->GetLabel()->label_.ToString();
    while (current_trace_pointer != nullptr &&
        !used[block_label]) {
      used[block_label] = true;
      current_trace.AddNextBlock(*current_trace_pointer);
      if (current_trace_pointer->GetJump()->GetNodeType() == IRT::NodeType::CJUMP) {
        IRT::JumpConditionalStatement* jump_stmt = dynamic_cast<IRT::JumpConditionalStatement*>(
            current_trace_pointer->GetJump()
        );
//        if (label_to_block_.find(jump_stmt))
        std::string false_label = jump_stmt->label_false_.ToString();
        std::string true_label = jump_stmt->label_true_.ToString();
        if (!used[false_label]) {
          current_trace_pointer = label_to_block_[false_label];
        } else {
          current_trace_pointer = label_to_block_[true_label];
        }
//        current_trace_pointer = &label_to_block_[jump_stmt->label_false_.ToString()];
      } else {
        IRT::JumpStatement* jump_stmt = dynamic_cast<IRT::JumpStatement*>(
            current_trace_pointer->GetJump()
        );
        current_trace_pointer = label_to_block_[jump_stmt->label_.ToString()];
      }

      if (current_trace_pointer != nullptr) {
        block_label = current_trace_pointer->GetLabel()->label_.ToString();
      }
    }
  }
  return traces;
}

void Driver::PrintTraces() {
  std::string prefix_path = "ir_canonic_test/trash_folder/";
  for (auto& trace_vector : traces_) {
    IRT::PrintVisitor traces_print_visitor(prefix_path + trace_vector.first + "_traces.txt");
    size_t trace_index = 0;
    for (auto& trace : trace_vector.second) {
      std::string trace_str = "Trace separator EKKEKEKEKEKKEKEKEKEKKEKEKKEKEKEKEKEKEKKEKEKEKEKKEKEKE\n";
      traces_print_visitor.PrintString(trace_str);
      size_t block_index = 0;
      for (auto& block : trace.GetBlockSequence()) {
        std::string block_str = "Block separator EHHEHEHEHHEHEHEHEHHEHEHEHHEHEHEHHEHEHEHHEHEHEHEHHEH\n";
        traces_print_visitor.PrintString(block_str);
        block.GetLabel()->Accept(&traces_print_visitor);
        for (auto stmt : block.GetStatements()) {
          stmt->Accept(&traces_print_visitor);
        }
        block.GetJump()->Accept(&traces_print_visitor);
        ++block_index;
      }
      ++trace_index;
    }
  }
}

