#pragma once

#include <objects/Method.h>
#include <stack>
#include <functions/Function.h>

#include <memory>
class FrameEmulator {
 public:
  explicit FrameEmulator(std::shared_ptr<Method> function);
  void SetParams(const std::vector<int>& values);

  size_t AllocVariable();

  void DeallocScope();
  void AllocScope();

  int Get(int index) const;

  void Set(int index, int value);

  void SetParentFrame(FrameEmulator* frame);

  int GetReturnValue() const;

  void SetParentReturnValue(int value);

  bool HasParent();

 private:
  std::stack<int> offsets_;
  std::vector<int> params_;
  std::vector<int> variables_;

  int return_value_ = 0;

  void SetReturnValue(int value);

  FrameEmulator* parent_frame = nullptr;

};



