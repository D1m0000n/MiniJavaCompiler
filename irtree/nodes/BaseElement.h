#pragma once

#include "../visitors/Visitor.h"
namespace IRT {

enum class NodeType : char {
  BINOP,
  CALL,
  CONST,
  ESEQ,
  MEM,
  NAME,
  TEMP,
  EXP,
  JUMP,
  CJUMP,
  LABEL,
  MOVE,
  SEQ,
  EXPLIST,
  PRINT
};

class BaseElement {
 public:
  virtual ~BaseElement() = default;
  virtual void Accept(Visitor* visitor) = 0;
  virtual NodeType GetNodeType() = 0;
};
}
