#include "PrintOpCodeVisitor.h"

#include "BaseElements.h"

IRT::PrintOpCodeVisitor::PrintOpCodeVisitor(const std::string& filename) : stream_(filename) {}

IRT::PrintOpCodeVisitor::~PrintOpCodeVisitor() {
  stream_.close();
}

void IRT::PrintOpCodeVisitor::Visit(IRT::AddCode* code) {
  PrintTab();
  std::string hash = "";
  if (code->argb_type_ == OpType::CONST) {
    hash = "#";
  }
  stream_ << code->operation_ << code->suffix_ << " " << code->regd_ << ", " << code->rega_
  << ", " << hash << code->argb_ << "\n";
}

void IRT::PrintOpCodeVisitor::Visit(IRT::AndCode* code) {
  PrintTab();
  std::string hash = "";
  if (code->argb_type_ == OpType::CONST) {
    hash = "#";
  }
  stream_ << code->operation_ << code->suffix_ << " " << code->regd_ << ", " << code->rega_
  << ", " << hash << code->argb_ << "\n";
}

void IRT::PrintOpCodeVisitor::Visit(IRT::CmpCode* code) {
  PrintTab();
  std::string hash = "";
  if (code->argb_type_ == OpType::CONST) {
    hash = "#";
  }
  stream_ << code->operation_ << code->suffix_  << " " << code->rega_ << ", " << hash << code->argb_ << '\n';
}

void IRT::PrintOpCodeVisitor::Visit(IRT::DivCode* code) {
  PrintTab();
  std::string hash = "";
  if (code->argb_type_ == OpType::CONST) {
    hash = "#";
  }
  stream_ << code->operation_ << code->suffix_ << " "  << code->regd_ << ", " << code->rega_
  << ", " << hash << code->argb_ << "\n";
}

void IRT::PrintOpCodeVisitor::Visit(IRT::JumpCode* code) {
  PrintTab();
  stream_ << code->operation_ << code->suffix_ << " " << code->label_ << '\n';
}

void IRT::PrintOpCodeVisitor::Visit(IRT::LabelCode* code) {
  stream_ << code->label_ << ":\n";
}

void IRT::PrintOpCodeVisitor::Visit(IRT::LdrCode* code) {
  PrintTab();
  std::string comma = "";
  if (code->regaddr_type_ != OpType::NONE) {
    comma = ", ";
  }
  stream_ << code->operation_ << code->suffix_ << " " <<  code->regd_
  << ", [" << code->regaddr_ << comma << '#' <<  code->offset_ << "]\n";
}

void IRT::PrintOpCodeVisitor::Visit(IRT::MovCode* code) {
  PrintTab();
  std::string hash = "";
  if (code->arg_type_ == OpType::CONST) {
    hash = "#";
  }
  stream_ << code->operation_ << code->suffix_ << " " << code->regd_
  << ", " << hash << code->arg_ << '\n';
}

void IRT::PrintOpCodeVisitor::Visit(IRT::MulCode* code) {
  PrintTab();
  std::string hash = "";
  if (code->argb_type_ == OpType::CONST) {
    hash = "#";
  }
  stream_ << code->operation_ << code->suffix_ << " " << code->regd_ << ", " << code->rega_
  << ", " << hash << code->argb_ << "\n";
}

void IRT::PrintOpCodeVisitor::Visit(IRT::OrCode* code) {
  PrintTab();
  std::string hash = "";
  if (code->argb_type_ == OpType::CONST) {
    hash = "#";
  }
  stream_ << code->operation_ << code->suffix_ << " " << code->regd_ << ", " << code->rega_
  << ", " << hash << code->argb_ << "\n";
}

void IRT::PrintOpCodeVisitor::Visit(IRT::PopCode* code) {
  PrintTab();
  stream_ << code->operation_ << " " << code->reg_ << '\n';
}

void IRT::PrintOpCodeVisitor::Visit(IRT::PushCode* code) {
  PrintTab();
  stream_ << code->operation_ << " " << code->reg_ << '\n';
}

void IRT::PrintOpCodeVisitor::Visit(IRT::StrCode* code) {
  PrintTab();
  std::string comma = "";
  if (code->regaddr_type_ != OpType::NONE) {
    comma = ", ";
  }
  stream_ << code->operation_ << code->suffix_ << " " <<  code->regs_
          << ", [" << code->regaddr_ << comma << '#' << code->offset_ << "]\n";
}

void IRT::PrintOpCodeVisitor::Visit(IRT::SubCode* code) {
  PrintTab();
  std::string hash = "";
  if (code->argb_type_ == OpType::CONST) {
    hash = "#";
  }
  stream_ << code->operation_ << code->suffix_ << " " << code->regd_ << ", " << code->rega_
  << ", " << hash << code->argb_ << "\n";
}

void IRT::PrintOpCodeVisitor::PrintTab() {
  stream_ << '\t';
}

void IRT::PrintOpCodeVisitor::Visit(IRT::PushListCode* list) {
  PrintTab();
  stream_ << list->operation_ << " {";
  for (size_t i = 0; i < list->registers_.size() - 1; ++i) {
    stream_ << "r" << list->registers_[i] << ", ";
  }
  stream_ << "r" << list->registers_.back() << "}\n";
}

void IRT::PrintOpCodeVisitor::Visit(IRT::PopListCode* list) {
  PrintTab();
  stream_ << list->operation_ << " {";
  for (size_t i = 0; i < list->registers_.size() - 1; ++i) {
    stream_ << "r" << list->registers_[i] << ", ";
  }
  stream_ << "r" << list->registers_.back() << "}\n";
}
