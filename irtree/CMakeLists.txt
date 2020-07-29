#add_subdirectory(generators)
#add_subdirectory(nodes)
#add_subdirectory(tree_wrapper)

set(
        SOURCES
        generators/Label.cpp
        generators/Label.h
        generators/Temporary.cpp
        generators/Temporary.h

        tree_wrapper/SubtreeWrapper.h
        tree_wrapper/ExpressionWrapper.cpp
        tree_wrapper/ExpressionWrapper.h
        tree_wrapper/StatementWrapper.cpp
        tree_wrapper/StatementWrapper.h
        tree_wrapper/conditional_wrappers/ConditionalWrapper.cpp
        tree_wrapper/conditional_wrappers/ConditionalWrapper.h
        tree_wrapper/conditional_wrappers/NegateConditionalWrapper.cpp
        tree_wrapper/conditional_wrappers/NegateConditionalWrapper.h
        tree_wrapper/conditional_wrappers/AndConditionalWrapper.cpp
        tree_wrapper/conditional_wrappers/AndConditionalWrapper.h
        tree_wrapper/conditional_wrappers/OrConditionalWrapper.cpp
        tree_wrapper/conditional_wrappers/OrConditionalWrapper.h
        tree_wrapper/conditional_wrappers/RelativeConditionalWrapper.cpp
        tree_wrapper/conditional_wrappers/RelativeConditionalWrapper.h

        nodes/BaseElement.h

        nodes/statements/Statement.h
        nodes/statements/ExpStatement.cpp
        nodes/statements/ExpStatement.h
        nodes/statements/JumpConditionalStatement.cpp
        nodes/statements/JumpConditionalStatement.h
        nodes/statements/MoveStatement.cpp
        nodes/statements/MoveStatement.h
        nodes/statements/SeqStatement.cpp
        nodes/statements/SeqStatement.h
        nodes/statements/LabelStatement.cpp
        nodes/statements/LabelStatement.h
        nodes/statements/JumpStatement.cpp
        nodes/statements/JumpStatement.h
        nodes/statements/PrintStatement.h
        nodes/statements/PrintStatement.cpp

        nodes/expressions/Expression.h
        nodes/expressions/ConstExpression.cpp
        nodes/expressions/ConstExpression.h
        nodes/expressions/BinopExpression.cpp
        nodes/expressions/BinopExpression.h
        nodes/expressions/TempExpression.cpp
        nodes/expressions/TempExpression.h
        nodes/expressions/MemExpression.cpp
        nodes/expressions/MemExpression.h
        nodes/expressions/CallExpression.cpp
        nodes/expressions/CallExpression.h
        nodes/expressions/NameExpression.cpp
        nodes/expressions/NameExpression.h
        nodes/expressions/EseqExpression.cpp
        nodes/expressions/EseqExpression.h

        nodes/ExpressionList.cpp
        nodes/ExpressionList.h


        types/LogicOperatorType.h
        types/BinaryOperatorType.h
        types/LogicOperatorType.cpp
        types/BinaryOperatorType.cpp

        visitors/Visitor.h
        visitors/VisitorStruct.h
        visitors/BaseElements.h
        visitors/PrintVisitor.cpp
        visitors/PrintVisitor.h
        visitors/TemplateVisitor.h
        visitors/TemplateVisitor.cpp
        visitors/DoubleCallEliminateVisitor.h
        visitors/DoubleCallEliminateVisitor.cpp
        visitors/EseqEliminateVisitor.h
        visitors/EseqEliminateVisitor.cpp
        visitors/LinearizeVisitor.h
        visitors/LinearizeVisitor.cpp
        visitors/AssemblyCodeGenerator.h
        visitors/AssemblyCodeGenerator.cpp
        visitors/OpCodeVisitor.h
        visitors/PrintOpCodeVisitor.h
        visitors/PrintOpCodeVisitor.cpp
        visitors/ConflictsGraphVisitor.h
        visitors/ConflictsGraphVisitor.cpp
        visitors/PrintPhysRegVisitor.h
        visitors/PrintPhysRegVisitor.cpp

        blocks/Block.h
        blocks/Block.cpp

        traces/Trace.h
        traces/Trace.cpp

        opcodes/OpCode.h
        opcodes/AddCode.h
        opcodes/AddCode.cpp
        opcodes/AndCode.h
        opcodes/AndCode.cpp
        opcodes/OrCode.h
        opcodes/OrCode.cpp
        opcodes/SubCode.h
        opcodes/SubCode.cpp
        opcodes/MovCode.h
        opcodes/MovCode.cpp
        opcodes/JumpCode.h
        opcodes/JumpCode.cpp
        opcodes/CmpCode.h
        opcodes/CmpCode.cpp
        opcodes/StrCode.h
        opcodes/StrCode.cpp
        opcodes/LabelCode.h
        opcodes/LabelCode.cpp
        opcodes/MulCode.h
        opcodes/MulCode.cpp
        opcodes/DivCode.h
        opcodes/DivCode.cpp
        opcodes/LdrCode.h
        opcodes/LdrCode.cpp
        opcodes/PushCode.h
        opcodes/PushCode.cpp
        opcodes/PopCode.h
        opcodes/PopCode.cpp
        opcodes/PushListCode.h
        opcodes/PushListCode.cpp
        opcodes/PopListCode.h
        opcodes/PopListCode.cpp
)

add_library(${IR_LIB} ${SOURCES})