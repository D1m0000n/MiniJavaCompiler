#include "ConflictsGraphVisitor.h"
#include "BaseElements.h"

IRT::ConflictsGraphVisitor::ConflictsGraphVisitor(std::set<int> live_in, int inst_quantity) :
    live_in_(live_in), inst_quantity_(inst_quantity) {
  inst_counter_ = 0;
  def_.resize(inst_quantity);
  use_.resize(inst_quantity);
  in_.resize(inst_quantity);
  out_.resize(inst_quantity);
  live_in_to_next_ = false;
  base_point_offset_ = 4;
}

int IRT::ConflictsGraphVisitor::GetTempNumber(std::string temp) {
  std::string res;
  for (int i = 1; i < temp.size(); ++i) {
    res.push_back(temp[i]);
  }
  int result = std::stoi(res);
  return result;
//  int mul = 1;
//  for (int i = temp.size() - 1; i >= 1; --i) {
//    result += (temp[i] - '0') * mul;
//    mul *= 10;
//  }
//  return result;
}

void IRT::ConflictsGraphVisitor::Visit(IRT::LabelCode* code) {
  //// live_in already set
  ++inst_counter_;
}

void IRT::ConflictsGraphVisitor::Visit(IRT::AddCode* code) {
  if (code->regd_type_ == OpType::TEMP) {
    int regd = GetTempNumber(code->regd_);
    def_[inst_counter_].insert(regd);
  }
  if (code->rega_type_ == OpType::TEMP) {
    int rega = GetTempNumber(code->rega_);
    use_[inst_counter_].insert(rega);
  }
  if (code->argb_type_ == OpType::TEMP) {
    int argb = GetTempNumber(code->argb_);
    use_[inst_counter_].insert(argb);
  }
  ++inst_counter_;
}

void IRT::ConflictsGraphVisitor::Visit(IRT::AndCode* code) {
  if (code->regd_type_ == OpType::TEMP) {
    int regd = GetTempNumber(code->regd_);
    def_[inst_counter_].insert(regd);
  }
  if (code->rega_type_ == OpType::TEMP) {
    int rega = GetTempNumber(code->rega_);
    use_[inst_counter_].insert(rega);
  }
  if (code->argb_type_ == OpType::TEMP) {
    int argb = GetTempNumber(code->argb_);
    use_[inst_counter_].insert(argb);
  }
  ++inst_counter_;
}

void IRT::ConflictsGraphVisitor::Visit(IRT::DivCode* code) {
  if (code->regd_type_ == OpType::TEMP) {
    int regd = GetTempNumber(code->regd_);
    def_[inst_counter_].insert(regd);
  }
  if (code->rega_type_ == OpType::TEMP) {
    int rega = GetTempNumber(code->rega_);
    use_[inst_counter_].insert(rega);
  }
  if (code->argb_type_ == OpType::TEMP) {
    int argb = GetTempNumber(code->argb_);
    use_[inst_counter_].insert(argb);
  }
  ++inst_counter_;
}

void IRT::ConflictsGraphVisitor::Visit(IRT::MulCode* code) {
  if (code->regd_type_ == OpType::TEMP) {
    int regd = GetTempNumber(code->regd_);
    def_[inst_counter_].insert(regd);
  }
  if (code->rega_type_ == OpType::TEMP) {
    int rega = GetTempNumber(code->rega_);
    use_[inst_counter_].insert(rega);
  }
  if (code->argb_type_ == OpType::TEMP) {
    int argb = GetTempNumber(code->argb_);
    use_[inst_counter_].insert(argb);
  }
  ++inst_counter_;
}

void IRT::ConflictsGraphVisitor::Visit(IRT::OrCode* code) {
  if (code->regd_type_ == OpType::TEMP) {
    int regd = GetTempNumber(code->regd_);
    def_[inst_counter_].insert(regd);
  }
  if (code->rega_type_ == OpType::TEMP) {
    int rega = GetTempNumber(code->rega_);
    use_[inst_counter_].insert(rega);
  }
  if (code->argb_type_ == OpType::TEMP) {
    int argb = GetTempNumber(code->argb_);
    use_[inst_counter_].insert(argb);
  }
  ++inst_counter_;
}

void IRT::ConflictsGraphVisitor::Visit(IRT::SubCode* code) {
  if (code->regd_type_ == OpType::TEMP) {
    int regd = GetTempNumber(code->regd_);
    def_[inst_counter_].insert(regd);
  }
  if (code->rega_type_ == OpType::TEMP) {
    int rega = GetTempNumber(code->rega_);
    use_[inst_counter_].insert(rega);
  }
  if (code->argb_type_ == OpType::TEMP) {
    int argb = GetTempNumber(code->argb_);
    use_[inst_counter_].insert(argb);
  }
  ++inst_counter_;
}

void IRT::ConflictsGraphVisitor::Visit(IRT::PushListCode* list) {}

void IRT::ConflictsGraphVisitor::Visit(IRT::PopListCode* list) {}

void IRT::ConflictsGraphVisitor::Visit(IRT::CmpCode* code) {
  if (code->rega_type_ == OpType::TEMP) {
    int rega = GetTempNumber(code->rega_);
    use_[inst_counter_].insert(rega);
  }
  if (code->argb_type_ == OpType::TEMP) {
    int argb = GetTempNumber(code->argb_);
    use_[inst_counter_].insert(argb);
  }
  ++inst_counter_;
}

void IRT::ConflictsGraphVisitor::Visit(IRT::LdrCode* code) {
  if (code->regd_type_ == OpType::TEMP) {
    int regd = GetTempNumber(code->regd_);
    def_[inst_counter_].insert(regd);
  }
  if (code->regaddr_type_ == OpType::TEMP) {
    int regaddr = GetTempNumber(code->regaddr_);
    use_[inst_counter_].insert(regaddr);
  }
  ++inst_counter_;
}

void IRT::ConflictsGraphVisitor::Visit(IRT::StrCode* code) {
  if (code->regs_type_ == OpType::TEMP) {
    int regs = GetTempNumber(code->regs_);
    use_[inst_counter_].insert(regs);
  }
  if (code->regaddr_type_ == OpType::TEMP) {
    int regaddr = GetTempNumber(code->regaddr_);
    use_[inst_counter_].insert(regaddr);
  }
  ++inst_counter_;
}

void IRT::ConflictsGraphVisitor::Visit(IRT::PopCode* code) {
  if (code->reg_type_ == OpType::TEMP) {
    int reg = GetTempNumber(code->reg_);
    use_[inst_counter_].insert(reg);
  }
  ++inst_counter_;
}

void IRT::ConflictsGraphVisitor::Visit(IRT::PushCode* code) {
  if (code->reg_type_ == OpType::TEMP) {
    int reg = GetTempNumber(code->reg_);
    use_[inst_counter_].insert(reg);
  }
  ++inst_counter_;
}

void IRT::ConflictsGraphVisitor::Visit(IRT::JumpCode* code) {
  if (code->suffix_ != "") {
    live_in_to_next_ = true;
  }
  jump_label_ = code->label_;
  ++inst_counter_;
  CalculateConflicts();
}

void IRT::ConflictsGraphVisitor::Visit(IRT::MovCode* code) {
  if (code->regd_type_ == OpType::TEMP &&
      code->arg_type_ == OpType::TEMP) {
    int regd = GetTempNumber(code->regd_);
    int arg = GetTempNumber(code->arg_);
    move_list_.emplace_back(regd, arg);
  }
  if (code->regd_type_ == OpType::REG &&
      code->arg_type_ == OpType::TEMP) {
    int arg = GetTempNumber(code->arg_);
    use_[inst_counter_].insert(arg);
  }
  if (code->regd_type_ == OpType::TEMP &&
      code->arg_type_ == OpType::CONST) {
    int regd = GetTempNumber(code->regd_);
    def_[inst_counter_].insert(regd);
  }
  ++inst_counter_;
}

std::string IRT::ConflictsGraphVisitor::GetJumpLabel() {
  return jump_label_;
}

void IRT::ConflictsGraphVisitor::CalculateConflicts() {
  MakeInOut();
  //// pair for type of edge(0 - real conflict, 1 - may be conflict)
  std::unordered_map<int, std::set<std::pair<int, int>>> graph;
  for (int i = 0; i < inst_quantity_ - 1; ++i) {
    auto intersect = IntersectSets(out_[i], in_[i + 1]);
    for (auto from : intersect) {
      for (auto to : intersect) {
        if (from == to) continue;
        graph[from].insert({to, 0});
      }
    }
  }
  for (auto e : move_list_) {
    if (graph[e.first].find({e.second, 0}) != graph[e.first].end()) {
      graph[e.first].insert({e.second, 1});
    }
    if (graph[e.second].find({e.first, 0}) != graph[e.second].end()) {
      graph[e.second].insert({e.first, 1});
    }
  }
  //// graph of conflicts is built
  if (graph.size() <= 11) { //// 11 is allowed registers (from r0 to r10)
    int counter = 0;        //// because we saved all callee-save registers
    for (auto e : graph) {
      AddPhysReg(e.first, counter++);
    }
    return;
  }

//  std::unordered_map<int, std::set<std::pair<int, int>>> conflicts;
  std::unordered_map<int, int> degs;
  std::unordered_map<int, bool> used;
  for (auto e : graph) {
    degs[e.first] = e.second.size();
    used[e.first] = false;
  }
  std::stack<std::pair<int, int>> color_order; //// second parameter means candidate type of vertex
                                               //// 0 - normal vertex, 1 - candidate to save in memory
  for (int j = 0; j < graph.size(); ++j) {
    bool vertex_deleted = false;
    for (auto vertex : degs) {
      if (!used[vertex.first] && vertex.second < 11) {
        used[vertex.first] = true;
        for (auto to : graph[vertex.first]) {
          --degs[to.first];
        }
        vertex_deleted = true;
        color_order.push({vertex.first, 0});
        break;
      }
    }
    if (!vertex_deleted) {
      for (auto vertex : degs) {
        if (!used[vertex.first]) {
          used[vertex.first] = true;
          for (auto to : graph[vertex.first]) {
            --degs[to.first];
          }
          color_order.push({vertex.first, 1});
        }
      }
    }
  }
  std::unordered_map<int, int> colors; //// temp -> color
  for (auto e : graph) {
    colors[e.first] = -1;
  }
  //// color order build
  while (!color_order.empty()) {
    auto current_vertex = color_order.top();
    color_order.pop();
    auto neighbours = graph[current_vertex.first];
    std::set<int> mex;
    for (auto par : neighbours) { //// get neighbours colors
      if (colors[par.first] >= 0) {
        mex.insert(colors[par.first]);
      }
    }
    int color_result = MexCalc(mex);
    if (color_result < 11) {
      colors[current_vertex.first] = color_result;
    } else {
      colors[current_vertex.first] = -2; //// save to memory
      std::string temp = '%' + std::to_string(current_vertex.first);
      saved_in_memory_[temp] = base_point_offset_;
      base_point_offset_ += 4;
    }
  }
  for (auto color : colors) {
    if (color.second >= 0) {
      AddPhysReg(color.first, color.second);
    }
  }
}

void IRT::ConflictsGraphVisitor::MakeInOut() {
  if (inst_quantity_ == 0) { return; }
  if (inst_quantity_ <= 1) {
    in_[0] = live_in_;
    in_[0] = MergeSets(in_[0], use_[0]);
    return;
  }
  std::vector<std::set<int>> pred_in;
  while (true) {
    for (size_t i = 0; i < inst_quantity_ - 1; ++i) {
      if (i == 0) {
        in_[0] = live_in_;
        in_[0] = MergeSets(in_[0], use_[0]);
      } else {
        in_[i] = use_[i];
      }
      std::set<int> tmp = SubSets(out_[i], def_[i]);
      in_[i] = MergeSets(in_[i], tmp);
    }
    in_[inst_quantity_ - 1] = out_[inst_quantity_ - 2];
    for (size_t i = 1; i < inst_quantity_ - 1; ++i) {
      out_[i - 1] = in_[i];
    }
    if (pred_in == in_) {
      break;
    } else {
      pred_in = in_;
    }
  }
}

std::set<int> IRT::ConflictsGraphVisitor::MergeSets(std::set<int> first, std::set<int> second) {
  std::set<int> result = first;
  for (auto e : second) {
    result.insert(e);
  }
  return result;
}

std::set<int> IRT::ConflictsGraphVisitor::SubSets(std::set<int> first, std::set<int> second) {
  std::set<int> result = first;
  for (auto e : second) {
    result.erase(e);
  }
  return result;
}

std::unordered_map<std::string, int> IRT::ConflictsGraphVisitor::GetPhysRegs() {
  return temp_to_reg_;
}

std::set<int> IRT::ConflictsGraphVisitor::IntersectSets(std::set<int> first, std::set<int> second) {
  std::set<int> result;
  for (auto e : first) {
    if (second.find(e) != second.end()) {
      result.insert(e);
    }
  }
  return result;
}

void IRT::ConflictsGraphVisitor::AddPhysReg(int temp, int reg) {
  std::string temp_name = '%' + std::to_string(temp);
  temp_to_reg_[temp_name] = reg;
}

int IRT::ConflictsGraphVisitor::MexCalc(std::set<int> colors) {
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

std::unordered_map<std::string, int> IRT::ConflictsGraphVisitor::GetSavedInMemory() {
  return saved_in_memory_;
}
