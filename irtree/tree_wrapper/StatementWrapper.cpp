#include <cassert>
#include "StatementWrapper.h"

namespace IRT {

Expression* StatementWrapper::ToExpression() {
  assert(false);
}
Statement* StatementWrapper::ToStatement() {
  return statement_;
}

Statement* StatementWrapper::ToConditional(Label true_label, Label false_label) {
  assert(false);
}

StatementWrapper::StatementWrapper(Statement* statement) : statement_(statement) {}

}  // namespace IRT