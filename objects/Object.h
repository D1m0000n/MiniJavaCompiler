#pragma once

#include <utility>
#include <vector>
#include <string>
#include <stdexcept>

class Variable {
  Variable() = default;
  Variable(std::string type, std::string identifier) : type(std::move(type)), identifier(std::move(identifier)) {}
  std::string type;
  std::string identifier;
};

class Object {
 public:
  virtual int ToInt();
  virtual int ToBoolean();
  virtual std::string Type();
  virtual ~Object() = default;
};