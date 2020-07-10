#pragma once

#include <string>
#include <vector>
#include <base_elements/BaseElement.h>

class ParamList : public BaseElement {
 public:
  ParamList();
  explicit ParamList(const std::string& type, const std::string& param);
  void Accept(Visitor *visitor) override;
  void AddParam(const std::string& type, const std::string& param);
 public:
  std::vector<std::string> types_;
  std::vector<std::string> params_;
};



