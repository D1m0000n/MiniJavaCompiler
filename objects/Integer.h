#pragma once

#include "Object.h"

class Integer: public Object {
 public:
    explicit Integer(int value);
    int ToInt() override;
    std::string Type() override;

 private:
    int value_;
};