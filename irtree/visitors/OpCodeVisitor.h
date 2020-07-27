#pragma once
//#include "BaseElements.h"

namespace IRT {

class AddCode;
class AndCode;
class CmpCode;
class DivCode;
class JumpCode;
class LabelCode;
class LdrCode;
class MovCode;
class MulCode;
class OrCode;
class PopCode;
class PushCode;
class StrCode;
class SubCode;

class OpCodeVisitor {
 public:
  virtual ~OpCodeVisitor() = default;

  virtual void Visit(AddCode* code) = 0;
  virtual void Visit(AndCode* code) = 0;
  virtual void Visit(CmpCode* code) = 0;
  virtual void Visit(DivCode* code) = 0;
  virtual void Visit(JumpCode* code) = 0;
  virtual void Visit(LabelCode* code) = 0;
  virtual void Visit(LdrCode* code) = 0;
  virtual void Visit(MovCode* code) = 0;
  virtual void Visit(MulCode* code) = 0;
  virtual void Visit(OrCode* code) = 0;
  virtual void Visit(PopCode* code) = 0;
  virtual void Visit(PushCode* code) = 0;
  virtual void Visit(StrCode* code) = 0;
  virtual void Visit(SubCode* code) = 0;

};
};