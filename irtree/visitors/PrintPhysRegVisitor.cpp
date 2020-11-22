#pragma once

#include "PrintPhysRegVisitor.h"

#include "BaseElements.h"

IRT::PrintPhysRegVisitor::~PrintPhysRegVisitor() {
  stream_.close();
}

void IRT::PrintPhysRegVisitor::Visit(IRT::AddCode* code) {
  std::string regd;
  std::string rega;
  std::string argb;
  std::vector<std::string> args;
  std::vector<bool> saved;
  std::vector<OpType> args_type;
  if (code->regd_type_ == OpType::TEMP) {
    bool is_saved = false;
    regd = GetReg(code->regd_, is_saved);
    saved.push_back(is_saved);
  } else {
    regd = code->regd_;
    saved.push_back(false);
  }
  args.push_back(regd);
  args_type.push_back(code->regd_type_);

  if (code->rega_type_ == OpType::TEMP) {
    bool is_saved = false;
    rega = GetReg(code->rega_, is_saved);
    saved.push_back(is_saved);
  } else {
    rega = code->rega_;
    saved.push_back(false);
  }
  args.push_back(rega);
  args_type.push_back(code->rega_type_);

  if (code->argb_type_ == OpType::CONST) {
    argb = "#" + code->argb_;
    saved.push_back(false);
  } else if (code->argb_type_ == OpType::TEMP) {
    bool is_saved = false;
    argb = GetReg(code->argb_, is_saved);
    saved.push_back(is_saved);
  } else {
    argb = code->argb_;
    saved.push_back(false);
  }
  args.push_back(argb);
  args_type.push_back(code->argb_type_);

  int counter = 0;
  for (auto e : saved) {
    counter += e;
  }

  if (counter == 0) {
    PrintTab();
    stream_ << code->operation_ << code->suffix_ << " " << regd << ", " << rega << ", " << argb << "\n";
  } else {
    SavePrint(code->operation_ + code->suffix_, args, args_type, saved);
  }
}

void IRT::PrintPhysRegVisitor::Visit(IRT::AndCode* code) {
  std::string regd;
  std::string rega;
  std::string argb;
  std::vector<std::string> args;
  std::vector<bool> saved;
  std::vector<OpType> args_type;
  if (code->regd_type_ == OpType::TEMP) {
    bool is_saved = false;
    regd = GetReg(code->regd_, is_saved);
    saved.push_back(is_saved);
  } else {
    regd = code->regd_;
    saved.push_back(false);
  }
  args.push_back(regd);
  args_type.push_back(code->regd_type_);

  if (code->rega_type_ == OpType::TEMP) {
    bool is_saved = false;
    rega = GetReg(code->rega_, is_saved);
    saved.push_back(is_saved);
  } else {
    rega = code->rega_;
    saved.push_back(false);
  }
  args.push_back(rega);
  args_type.push_back(code->rega_type_);

  if (code->argb_type_ == OpType::CONST) {
    argb = "#" + code->argb_;
    saved.push_back(false);
  } else if (code->argb_type_ == OpType::TEMP) {
    bool is_saved = false;
    argb = GetReg(code->argb_, is_saved);
    saved.push_back(is_saved);
  } else {
    argb = code->argb_;
    saved.push_back(false);
  }
  args.push_back(argb);
  args_type.push_back(code->argb_type_);

  int counter = 0;
  for (auto e : saved) {
    counter += e;
  }

  if (counter == 0) {
    PrintTab();
    stream_ << code->operation_ << code->suffix_ << " " << regd << ", " << rega << ", " << argb << "\n";
  } else {
    SavePrint(code->operation_ + code->suffix_, args, args_type, saved);
  }
}

IRT::PrintPhysRegVisitor::PrintPhysRegVisitor(const std::string& filename) : stream_(filename) {}

void IRT::PrintPhysRegVisitor::Visit(IRT::CmpCode* code) {
  std::string hash = "";
  std::string rega;
  std::string argb;
  if (code->rega_type_ == OpType::TEMP) {
    bool is_saved = false;
    rega = GetReg(code->rega_, is_saved);
  } else {
    rega = code->rega_;
  }

  if (code->argb_type_ == OpType::CONST) {
    argb = '#' + code->argb_;
  } else if (code->argb_type_ == OpType::TEMP) {
    bool is_saved = false;
    argb = GetReg(code->argb_, is_saved);
  } else {
    argb = code->argb_;
  }
  PrintTab();
  stream_ << code->operation_ << code->suffix_ << " " << rega << ", " << argb << '\n';
}

void IRT::PrintPhysRegVisitor::Visit(IRT::DivCode* code) {
  std::string regd;
  std::string rega;
  std::string argb;
  std::vector<std::string> args;
  std::vector<bool> saved;
  std::vector<OpType> args_type;
  if (code->regd_type_ == OpType::TEMP) {
    bool is_saved = false;
    regd = GetReg(code->regd_, is_saved);
    saved.push_back(is_saved);
  } else {
    regd = code->regd_;
    saved.push_back(false);
  }
  args.push_back(regd);
  args_type.push_back(code->regd_type_);

  if (code->rega_type_ == OpType::TEMP) {
    bool is_saved = false;
    rega = GetReg(code->rega_, is_saved);
    saved.push_back(is_saved);
  } else {
    rega = code->rega_;
    saved.push_back(false);
  }
  args.push_back(rega);
  args_type.push_back(code->rega_type_);

  if (code->argb_type_ == OpType::CONST) {
    argb = "#" + code->argb_;
    saved.push_back(false);
  } else if (code->argb_type_ == OpType::TEMP) {
    bool is_saved = false;
    argb = GetReg(code->argb_, is_saved);
    saved.push_back(is_saved);
  } else {
    argb = code->argb_;
    saved.push_back(false);
  }
  args.push_back(argb);
  args_type.push_back(code->argb_type_);

  int counter = 0;
  for (auto e : saved) {
    counter += e;
  }

  if (counter == 0) {
    PrintTab();
    stream_ << code->operation_ << code->suffix_ << " " << regd << ", " << rega << ", " << argb << "\n";
  } else {
    SavePrint(code->operation_ + code->suffix_, args, args_type, saved);
  }
}

void IRT::PrintPhysRegVisitor::Visit(IRT::JumpCode* code) {
  PrintTab();
  stream_ << code->operation_ << code->suffix_ << " " << code->label_ << '\n';
}

void IRT::PrintPhysRegVisitor::Visit(IRT::LabelCode* code) {
  stream_ << code->label_ << ":\n";
}

void IRT::PrintPhysRegVisitor::Visit(IRT::LdrCode* code) {
  std::string comma = "";
  std::string regaddr;
  std::string regd;

  if (code->regd_type_ == OpType::TEMP) {
    bool is_saved = false;
    regd = GetReg(code->regd_, is_saved);
  } else {
    regd = code->regd_;
  }

  if (code->regaddr_type_ != OpType::NONE) {
    comma = ", ";
    if (code->regaddr_type_ == OpType::TEMP) {
      bool is_saved = false;
      regaddr = GetReg(code->regaddr_, is_saved);
    } else {
      regaddr = code->regaddr_;
    }
  } else {
    regaddr = "";
  }

  PrintTab();
  stream_ << code->operation_ << code->suffix_ << " " << regd
          << ", [" << regaddr << comma << '#' << code->offset_ << "]\n";
}

void IRT::PrintPhysRegVisitor::Visit(IRT::MovCode* code) {
  PrintTab();
  std::string regd;
  std::string arg;
  if (code->regd_type_ == OpType::TEMP) {
    bool is_saved = false;
    regd = GetReg(code->regd_, is_saved);
  } else {
    regd = code->regd_;
  }

  if (code->arg_type_ == OpType::CONST) {
    arg = "#" + code->arg_;
  } else if (code->arg_type_ == OpType::TEMP) {
    bool is_saved = false;
    arg = GetReg(code->arg_, is_saved);
  } else {
    arg = code->arg_;
  }
  stream_ << code->operation_ << code->suffix_ << " " << regd << ", " << arg << '\n';
}

void IRT::PrintPhysRegVisitor::Visit(IRT::MulCode* code) {
  std::string regd;
  std::string rega;
  std::string argb;
  std::vector<std::string> args;
  std::vector<bool> saved;
  std::vector<OpType> args_type;
  if (code->regd_type_ == OpType::TEMP) {
    bool is_saved = false;
    regd = GetReg(code->regd_, is_saved);
    saved.push_back(is_saved);
  } else {
    regd = code->regd_;
    saved.push_back(false);
  }
  args.push_back(regd);
  args_type.push_back(code->regd_type_);

  if (code->rega_type_ == OpType::TEMP) {
    bool is_saved = false;
    rega = GetReg(code->rega_, is_saved);
    saved.push_back(is_saved);
  } else {
    rega = code->rega_;
    saved.push_back(false);
  }
  args.push_back(rega);
  args_type.push_back(code->rega_type_);

  if (code->argb_type_ == OpType::CONST) {
    argb = "#" + code->argb_;
    saved.push_back(false);
  } else if (code->argb_type_ == OpType::TEMP) {
    bool is_saved = false;
    argb = GetReg(code->argb_, is_saved);
    saved.push_back(is_saved);
  } else {
    argb = code->argb_;
    saved.push_back(false);
  }
  args.push_back(argb);
  args_type.push_back(code->argb_type_);

  int counter = 0;
  for (auto e : saved) {
    counter += e;
  }

  if (counter == 0) {
    PrintTab();
    stream_ << code->operation_ << code->suffix_ << " " << regd << ", " << rega << ", " << argb << "\n";
  } else {
    SavePrint(code->operation_ + code->suffix_, args, args_type, saved);
  }
}

void IRT::PrintPhysRegVisitor::Visit(IRT::OrCode* code) {
  std::string regd;
  std::string rega;
  std::string argb;
  std::vector<std::string> args;
  std::vector<bool> saved;
  std::vector<OpType> args_type;
  if (code->regd_type_ == OpType::TEMP) {
    bool is_saved = false;
    regd = GetReg(code->regd_, is_saved);
    saved.push_back(is_saved);
  } else {
    regd = code->regd_;
    saved.push_back(false);
  }
  args.push_back(regd);
  args_type.push_back(code->regd_type_);

  if (code->rega_type_ == OpType::TEMP) {
    bool is_saved = false;
    rega = GetReg(code->rega_, is_saved);
    saved.push_back(is_saved);
  } else {
    rega = code->rega_;
    saved.push_back(false);
  }
  args.push_back(rega);
  args_type.push_back(code->rega_type_);

  if (code->argb_type_ == OpType::CONST) {
    argb = "#" + code->argb_;
    saved.push_back(false);
  } else if (code->argb_type_ == OpType::TEMP) {
    bool is_saved = false;
    argb = GetReg(code->argb_, is_saved);
    saved.push_back(is_saved);
  } else {
    argb = code->argb_;
    saved.push_back(false);
  }
  args.push_back(argb);
  args_type.push_back(code->argb_type_);

  int counter = 0;
  for (auto e : saved) {
    counter += e;
  }

  if (counter == 0) {
    PrintTab();
    stream_ << code->operation_ << code->suffix_ << " " << regd << ", " << rega << ", " << argb << "\n";
  } else {
    SavePrint(code->operation_ + code->suffix_, args, args_type, saved);
  }
}

void IRT::PrintPhysRegVisitor::Visit(IRT::PopCode* code) {
  std::string reg;
  if (code->reg_type_ == OpType::TEMP) {
    bool is_saved = false;
    reg = GetReg(code->reg_, is_saved);
  } else {
    reg = code->reg_;
  }
  PrintTab();
  stream_ << code->operation_ << " " << reg << '\n';
}

void IRT::PrintPhysRegVisitor::Visit(IRT::PushCode* code) {
  std::string reg;
  if (code->reg_type_ == OpType::TEMP) {
    bool is_saved = false;
    reg = GetReg(code->reg_, is_saved);
  } else {
    reg = code->reg_;
  }
  PrintTab();
  stream_ << code->operation_ << " " << reg << '\n';
}

void IRT::PrintPhysRegVisitor::Visit(IRT::StrCode* code) {
  std::string comma = "";
  std::string regaddr;
  std::string regs;

  if (code->regs_type_ == OpType::TEMP) {
    bool is_saved = false;
    regs = GetReg(code->regs_, is_saved);
  } else {
    regs = code->regs_;
  }

  if (code->regaddr_type_ != OpType::NONE) {
    comma = ", ";
    if (code->regaddr_type_ == OpType::TEMP) {
      bool is_saved = false;
      regaddr = GetReg(code->regaddr_, is_saved);
    } else {
      regaddr = code->regaddr_;
    }
  } else {
    regaddr = "";
  }

  PrintTab();
  stream_ << code->operation_ << code->suffix_ << " " << regs
          << ", [" << regaddr << comma << '#' << code->offset_ << "]\n";
}

void IRT::PrintPhysRegVisitor::Visit(IRT::SubCode* code) {
  std::string regd;
  std::string rega;
  std::string argb;
  std::vector<std::string> args;
  std::vector<bool> saved;
  std::vector<OpType> args_type;
  if (code->regd_type_ == OpType::TEMP) {
    bool is_saved = false;
    regd = GetReg(code->regd_, is_saved);
    saved.push_back(is_saved);
  } else {
    regd = code->regd_;
    saved.push_back(false);
  }
  args.push_back(regd);
  args_type.push_back(code->regd_type_);

  if (code->rega_type_ == OpType::TEMP) {
    bool is_saved = false;
    rega = GetReg(code->rega_, is_saved);
    saved.push_back(is_saved);
  } else {
    rega = code->rega_;
    saved.push_back(false);
  }
  args.push_back(rega);
  args_type.push_back(code->rega_type_);

  if (code->argb_type_ == OpType::CONST) {
    argb = "#" + code->argb_;
    saved.push_back(false);
  } else if (code->argb_type_ == OpType::TEMP) {
    bool is_saved = false;
    argb = GetReg(code->argb_, is_saved);
    saved.push_back(is_saved);
  } else {
    argb = code->argb_;
    saved.push_back(false);
  }
  args.push_back(argb);
  args_type.push_back(code->argb_type_);

  int counter = 0;
  for (auto e : saved) {
    counter += e;
  }

  if (counter == 0) {
    PrintTab();
    stream_ << code->operation_ << code->suffix_ << " " << regd << ", " << rega << ", " << argb << "\n";
  } else {
    SavePrint(code->operation_ + code->suffix_, args, args_type, saved);
  }
}

void IRT::PrintPhysRegVisitor::PrintTab() {
  stream_ << '\t';
}

void IRT::PrintPhysRegVisitor::Visit(IRT::PushListCode* list) {
  PrintTab();
  stream_ << list->operation_ << " {";
  for (size_t i = 0; i < list->registers_.size() - 1; ++i) {
    stream_ << "r" << list->registers_[i] << ", ";
  }
  stream_ << "r" << list->registers_.back() << "}\n";
}

void IRT::PrintPhysRegVisitor::Visit(IRT::PopListCode* list) {
  PrintTab();
  stream_ << list->operation_ << " {";
  for (size_t i = 0; i < list->registers_.size() - 1; ++i) {
    stream_ << "r" << list->registers_[i] << ", ";
  }
  stream_ << "r" << list->registers_.back() << "}\n";
}

std::string IRT::PrintPhysRegVisitor::GetReg(std::string name, bool& is_saved) {
  std::string result;
  if (registers_.find(name) != registers_.end()) {
    result = 'r' + std::to_string(registers_[name]);
  } else if (saved_in_memory_.find(name) != saved_in_memory_.end()) {
    result = "";
    is_saved = true;
  } else {
    result = "r1";
  }
  return result;
}

void IRT::PrintPhysRegVisitor::SavePrint(std::string operation,
                                         std::vector<std::string> args,
                                         std::vector<OpType> args_type,
                                         std::vector<bool> saved) {
  std::set<int> used_registers;
  for (int i = 0; i < saved.size(); ++i) {
    if (saved[i]) continue;
    if (args_type[i] == OpType::TEMP || args_type[i] == OpType::REG) {
      std::string temp;
      for (int j = 1; j < args[i].size(); ++j) {
        temp.push_back(args[i][j]);
      }
      int reg = std::stoi(temp);
      used_registers.insert(reg);
      continue;
    }
  }

  std::vector<int> unused_registers;
  for (int i = 0; i < saved.size(); ++i) {
    if (saved[i]) {
      int mex = MexCalc(used_registers);
      unused_registers[i] = mex;
      used_registers.insert(mex);
    }
  }

  for (int i = 0; i < saved.size(); ++i) {
    if (saved[i]) {
      PrintTab();
      stream_ << "push r" << unused_registers[i] << '\n';
    }
  }

  std::string regd;
  std::string rega;
  std::string argb;
  if (!saved[0]) {
    regd = args[0];
  } else {
    PrintTab();
    int offset = saved_in_memory_[args[0]];
    stream_ << "ldr r" << unused_registers[0] << " [r11, #" << offset << "]\n";
  }
  if (!saved[1]) {
    rega = args[1];
  } else {
    PrintTab();
    int offset = saved_in_memory_[args[1]];
    stream_ << "ldr r" << unused_registers[1] << " [r11, #" << offset << "]\n";
  }
  if (!saved[2]) {
    argb = args[2];
  } else {
    PrintTab();
    int offset = saved_in_memory_[args[2]];
    stream_ << "ldr r" << unused_registers[2] << " [r11, #" << offset << "]\n";
  }
  PrintTab();
  stream_ << operation << regd << ", " << rega << ", " << argb << '\n';

  if (!saved[0]) {
    regd = args[0];
  } else {
    PrintTab();
    int offset = saved_in_memory_[args[0]];
    stream_ << "str r" << unused_registers[0] << " [r11, #" << offset << "]\n";
  }
  for (int i = 0; i < saved.size(); ++i) {
    if (saved[i]) {
      PrintTab();
      stream_ << "push r" << unused_registers[i] << '\n';
    }
  }
}

int IRT::PrintPhysRegVisitor::MexCalc(std::set<int> colors) {
  int ans = 0;
  while (true) {
    if (colors.find(ans) == colors.end()) {
      break;
    } else {
      ++ans;
    }
  }
  return ans;
}
void IRT::PrintPhysRegVisitor::SetRegsters(std::unordered_map<std::string, int> registers) {
  registers_ = registers;
}
void IRT::PrintPhysRegVisitor::SetSavedInMemory(std::unordered_map<std::string, int> saved) {
  saved_in_memory_ = saved;
}
