#pragma once

#include <symbol_table/Symbol.h>
#include <unordered_map>
#include <functions/Function.h>

class FunctionStorage {
 public:
  static FunctionStorage& GetInstance();
  void Set(Symbol symbol, Function* function);
  Function* Get(Symbol symbol) const;
  FunctionStorage(const FunctionStorage& other) = delete;

 private:
  FunctionStorage() = default;
  ~FunctionStorage() = default;
  FunctionStorage& operator=(const FunctionStorage&) = delete;
  std::unordered_map<Symbol, Function*> functions_;
};


