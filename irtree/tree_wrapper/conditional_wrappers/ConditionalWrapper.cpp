#include "ConditionalWrapper.h"
#include "../../generators/Temporary.h"
#include "../../nodes/expressions/TempExpression.h"
#include "../../nodes/expressions/ConstExpression.h"
#include "../../nodes/expressions/EseqExpression.h"
#include "../../nodes/statements/SeqStatement.h"
#include "../../nodes/statements/MoveStatement.h"
#include "../../nodes/statements/LabelStatement.h"

namespace IRT {
Expression* IRT::ConditionalWrapper::ToExpression() {
  auto* temp_expression = new TempExpression(Temporary());
  Label label_true;
  Label label_false;
  return new EseqExpression(
      new SeqStatement(
          new MoveStatement(new ConstExpression(1), temp_expression),
          new SeqStatement(
              ToConditional(label_true, label_false),
              new SeqStatement(
                  new LabelStatement(label_false),
                  new SeqStatement(
                      new MoveStatement(new ConstExpression(0), temp_expression),
                      new LabelStatement(label_true)
                  )
              )
          )
      ),
      temp_expression
  );
}

Statement* IRT::ConditionalWrapper::ToStatement() {
  return nullptr;
}

}