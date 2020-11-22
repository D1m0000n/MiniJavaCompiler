#pragma once

#include <string>
#include <fstream>
#include "OpCodeVisitor.h"

namespace IRT {
class PrintOpCodeVisitor : public OpCodeVisitor {
 public:
  explicit PrintOpCodeVisitor(const std::string& filename);
  ~PrintOpCodeVisitor() override;

  void Visit(AddCode* code) override;
  void Visit(AndCode* code) override;
  void Visit(CmpCode* code) override;
  void Visit(DivCode* code) override;
  void Visit(JumpCode* code) override;
  void Visit(LabelCode* code) override;
  void Visit(LdrCode* code) override;
  void Visit(MovCode* code) override;
  void Visit(MulCode* code) override;
  void Visit(OrCode* code) override;
  void Visit(PopCode* code) override;
  void Visit(PushCode* code) override;
  void Visit(StrCode* code) override;
  void Visit(SubCode* code) override;
  void Visit(PushListCode* list) override;
  void Visit(PopListCode* list) override;

 private:
  std::ofstream stream_;
  void PrintTab();
};
}  // namespace IRT
