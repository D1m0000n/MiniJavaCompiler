#pragma once

#include "../nodes/expressions/NameExpression.h"
#include "../nodes/expressions/CallExpression.h"
#include "../nodes/expressions/BinopExpression.h"
#include "../nodes/expressions/ConstExpression.h"
#include "../nodes/expressions/MemExpression.h"
#include "../nodes/expressions/TempExpression.h"
#include "../nodes/expressions/EseqExpression.h"
#include "../nodes/expressions/Expression.h"

#include "../nodes/statements/ExpStatement.h"
#include "../nodes/statements/JumpConditionalStatement.h"
#include "../nodes/statements/JumpStatement.h"
#include "../nodes/statements/LabelStatement.h"
#include "../nodes/statements/MoveStatement.h"
#include "../nodes/statements/SeqStatement.h"
#include "../nodes/statements/PrintStatement.h"

#include "../nodes/ExpressionList.h"

#include "../opcodes/AddCode.h"
#include "../opcodes/AndCode.h"
#include "../opcodes/OrCode.h"
#include "../opcodes/SubCode.h"

