#include "PrintOpCodeVisitor.h"

IRT::PrintOpCodeVisitor::PrintOpCodeVisitor(const std::string& filename) : stream_(filename) {}

IRT::PrintOpCodeVisitor::~PrintOpCodeVisitor() {
  stream_.close();
}

void IRT::PrintOpCodeVisitor::Visit(IRT::AddCode* code) {
  PrintTab();
  stream_ << code->operation_ << code->regd_ << ", " << code->rega_ << ", " << code->argb_ << "\n";
}

void IRT::PrintOpCodeVisitor::Visit(IRT::AndCode* code) {
  PrintTab();
  stream_ << code->operation_ << code->regd_ << ", " << code->rega_ << ", " << code->argb_ << "\n";
}

void IRT::PrintOpCodeVisitor::Visit(IRT::CmpCode* code) {
  PrintTab();
  stream_
}

void IRT::PrintOpCodeVisitor::Visit(IRT::DivCode* code) {
  PrintTab();
  stream_ << code->operation_ << code->regd_ << ", " << code->rega_ << ", " << code->argb_ << "\n";
}

void IRT::PrintOpCodeVisitor::Visit(IRT::JumpCode* code) {

}

void IRT::PrintOpCodeVisitor::Visit(IRT::LabelCode* code) {

}

void IRT::PrintOpCodeVisitor::Visit(IRT::LdrCode* code) {

}

void IRT::PrintOpCodeVisitor::Visit(IRT::MovCode* code) {

}

void IRT::PrintOpCodeVisitor::Visit(IRT::MulCode* code) {
  PrintTab();
  stream_ << code->operation_ << code->regd_ << ", " << code->rega_ << ", " << code->argb_ << "\n";
}

void IRT::PrintOpCodeVisitor::Visit(IRT::OrCode* code) {
  PrintTab();
  stream_ << code->operation_ << code->regd_ << ", " << code->rega_ << ", " << code->argb_ << "\n";
}

void IRT::PrintOpCodeVisitor::Visit(IRT::PopCode* code) {

}

void IRT::PrintOpCodeVisitor::Visit(IRT::PushCode* code) {

}

void IRT::PrintOpCodeVisitor::Visit(IRT::StrCode* code) {

}

void IRT::PrintOpCodeVisitor::Visit(IRT::SubCode* code) {
  PrintTab();
  stream_ << code->operation_ << code->regd_ << ", " << code->rega_ << ", " << code->argb_ << "\n";
}

void IRT::PrintOpCodeVisitor::PrintTab() {
  stream_ << '\t';
}
