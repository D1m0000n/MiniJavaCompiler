#include "ScopeLayer.h"

#include "objects/UninitObject.h"
#include "objects/Method.h"

#include <iostream>

ScopeLayer::ScopeLayer(ScopeLayer* parent) : parent_(parent) {
  std::cout << "Constructor called" << std::endl;
  std::cout << "End contstructor called" << std::endl;

  parent_->AddChild(this);

}

void ScopeLayer::AttachParent() {

}

ScopeLayer::ScopeLayer() : parent_(nullptr) {}

void ScopeLayer::DeclareVariable(Symbol symbol, const std::string& type) {
  if (values_.find(symbol) != values_.end()) {
    throw std::runtime_error("Variable has declared");
  }

  values_[symbol] = std::make_shared<UninitObject>(type);
  offsets_[symbol] = symbols_.size();
  symbols_.push_back(symbol);
}

void ScopeLayer::DeclareFunction(Symbol symbol, Function* function) {
  if (values_.find(symbol) != values_.end()) {
    throw std::runtime_error("Variable has declared");
  }

  values_[symbol] = std::make_shared<Method>(function->param_list_->params_);
}

void ScopeLayer::Put(Symbol symbol, std::shared_ptr<Object> value) {

  ScopeLayer* current_layer = this;

  while (!current_layer->Has(symbol) && current_layer->parent_ != nullptr) {
    current_layer = current_layer->parent_;
  }
  if (current_layer->Has(symbol)) {
    current_layer->values_.find(symbol)->second = value;
  } else {
    throw std::runtime_error("Variable not declared");
  }
}

bool ScopeLayer::Has(Symbol symbol) {
  return values_.find(symbol) != values_.end();
}

std::shared_ptr<Object> ScopeLayer::Get(Symbol symbol) {
  ScopeLayer* current_layer = this;

  while (!current_layer->Has(symbol) && current_layer->parent_ != nullptr) {
    current_layer = current_layer->parent_;
  }
  if (current_layer->Has(symbol)) {
    return current_layer->values_.find(symbol)->second;
  } else {
    throw std::runtime_error("Variable not declared");
  }
}

ScopeLayer* ScopeLayer::GetChild(size_t index) {
  std::cout << "Children of scope: " << children_.size() << std::endl;
  return children_[index];
}

void ScopeLayer::AddChild(ScopeLayer* child) {
  children_.push_back(child);
}

ScopeLayer* ScopeLayer::GetParent() const {
  return parent_;
}

void ScopeLayer::PrintLayer(std::ostream& stream, int num_tabs) const {

  for (const auto& symbol : symbols_) {
    for (int i = 0; i < num_tabs; ++i) {
      stream << "\t";
    }
    stream << symbol.GetName() << std::endl;
  }
  for (ScopeLayer* layer : children_) {
    layer->PrintLayer(stream, num_tabs + 1);
  }
}