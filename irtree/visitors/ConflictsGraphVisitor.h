#pragma once

#include <string>
#include <set>
#include <vector>
#include <unordered_map>
#include <stack>
#include "OpCodeVisitor.h"

namespace IRT {
class ConflictsGraphVisitor : public OpCodeVisitor {
 public:
  explicit ConflictsGraphVisitor(std::set<int> live_in, int instructions_quantity);

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

  std::string GetJumpLabel();
  std::unordered_map<std::string, int> GetPhysRegs();
  std::unordered_map<std::string, int> GetSavedInMemory();

 public:
  bool live_in_to_next_;

 private:
  int GetTempNumber(std::string temp);
  void CalculateConflicts();
  void MakeInOut();
  void AddPhysReg(int temp, int reg);
  int MexCalc(std::set<int> colors);
  std::set<int> MergeSets(std::set<int> first, std::set<int> second);
  std::set<int> SubSets(std::set<int> first, std::set<int> second);
  std::set<int> IntersectSets(std::set<int> first, std::set<int> second);

 private:
  std::string jump_label_;
  std::set<int> live_in_;
  int inst_counter_;
  int inst_quantity_;
  std::vector<std::set<int>> def_;
  std::vector<std::set<int>> use_;
  std::vector<std::set<int>> in_;
  std::vector<std::set<int>> out_;
  std::vector<std::pair<int, int>> move_list_;
  std::unordered_map<std::string, int> temp_to_reg_;
  std::unordered_map<std::string, int> saved_in_memory_; //// second if offset from base pointer
  int base_point_offset_;
};
}  // namespace IRT
