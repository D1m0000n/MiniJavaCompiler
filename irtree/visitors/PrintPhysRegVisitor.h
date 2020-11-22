#pragma once

#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <set>
#include <irtree/opcodes/OpCode.h>
#include "OpCodeVisitor.h"

namespace IRT {
class PrintPhysRegVisitor : public OpCodeVisitor {
 public:
  explicit PrintPhysRegVisitor(const std::string& filename);
  ~PrintPhysRegVisitor() override;

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

  void SetRegsters(std::unordered_map<std::string, int> registers);
  void SetSavedInMemory(std::unordered_map<std::string, int> saved);

 private:
  std::ofstream stream_;
  std::unordered_map<std::string, int> registers_;
  std::unordered_map<std::string, int> saved_in_memory_;
  void PrintTab();
  int MexCalc(std::set<int> colors);
  void SavePrint(std::string operation,
                 std::vector<std::string> args,
                 std::vector<OpType> args_type,
                 std::vector<bool> saved);
  std::string GetReg(std::string name, bool& is_saved);
};
}  // namespace IRT
