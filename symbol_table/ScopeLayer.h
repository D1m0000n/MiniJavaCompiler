#pragma once

#include "Symbol.h"
#include "objects/Object.h"
#include <functions/Function.h>

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>

class ScopeLayer {
 public:
  explicit ScopeLayer(ScopeLayer* parent);
  ScopeLayer();
  void DeclareVariable(Symbol symbol, const std::string& type);
  void DeclareFunction(Symbol symbol, Function* function);
  void Put(Symbol symbol, std::shared_ptr<Object> value);
  std::shared_ptr<Object> Get(Symbol symbol);
  bool Has(Symbol symbol);

  void AddChild(ScopeLayer* child);
  void AttachParent();

  ScopeLayer* GetChild(size_t index);
  ScopeLayer* GetParent() const;

  void PrintLayer(std::ostream& stream, int num_tabs) const;

 private:
  std::unordered_map<Symbol, std::shared_ptr<Object>> values_;
  std::unordered_map<Symbol, size_t> offsets_;
  std::vector<Symbol> symbols_;
  std::string name_;
  ScopeLayer* parent_;
  std::vector<ScopeLayer*> children_;
};