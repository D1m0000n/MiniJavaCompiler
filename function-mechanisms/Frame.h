#pragma once

#include <objects/Method.h>
#include <stack>
#include <functions/Function.h>

#include <memory>
class Frame {
 public:
  explicit Frame(std::shared_ptr<Method> function);
  void SetParams(const std::vector<int>& values);

  size_t AllocVariable();

  void DeallocScope();
  void AllocScope();

  int Get(int index) const;

  void Set(int index, int value);

  void SetParentFrame(Frame* frame);

  int GetReturnValue() const;

  void SetParentReturnValue(int value);

  bool HasParent();

 private:
  std::stack<int> offsets_;
  std::vector<int> params_;
  std::vector<int> variables_;

  int return_value_ = 0;

  void SetReturnValue(int value);

  Frame* parent_frame = nullptr;

};



