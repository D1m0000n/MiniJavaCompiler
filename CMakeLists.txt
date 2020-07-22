project(MiniJavaCompiler)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 14)

if (CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
    execute_process(
            COMMAND brew --prefix bison
            RESULT_VARIABLE BREW_BISON
            OUTPUT_VARIABLE BREW_BISON_PREFIX
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if (BREW_BISON EQUAL 0 AND EXISTS "${BREW_BISON_PREFIX}")
        message(STATUS "Found Bison keg installed by Homebrew at ${BREW_BISON_PREFIX}")
        set(BISON_EXECUTABLE "${BREW_BISON_PREFIX}/bin/bison")
    endif ()

    execute_process(
            COMMAND brew --prefix flex
            RESULT_VARIABLE BREW_FLEX
            OUTPUT_VARIABLE BREW_FLEX_PREFIX
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if (BREW_FLEX EQUAL 0 AND EXISTS "${BREW_FLEX_PREFIX}")
        message(STATUS "Found Flex keg installed by Homebrew at ${BREW_FLEX_PREFIX}")
        set(FLEX_EXECUTABLE "${BREW_FLEX_PREFIX}/bin/flex")
        include_directories(${BREW_FLEX_PREFIX}/include)
    endif ()
endif ()

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

include_directories(
        scanner
        driver
        expressions
        declarations
        assignments
        base_elements
        statements
        visitors
        main_class
        functions
        function-mechanisms
        .
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MiniJavaCompiler_SOURCE_DIR}/bin)

set(CURRENT_EXECUTABLE "${PROJECT_NAME}Executable")
set(GRAMMAR_LIB "${PROJECT_NAME}GrammarLib")
set(GRAMMAR_PROJECT "${PROJECT_NAME}GrammarProject")
set(IR_LIB "${PROJECT_NAME}IrLib")

set(
        HEADERS
        include/driver.hh
        parser.hh
)

BISON_TARGET(
        ParserScopes
        parser.y
        ${MiniJavaCompiler_SOURCE_DIR}/parser.cpp
        COMPILE_FLAGS --graph
        DEFINES_FILE ${MiniJavaCompiler_SOURCE_DIR}/parser.hh
)

FLEX_TARGET(
        ScannerScopes
        scanner.l
        ${MiniJavaCompiler_SOURCE_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(ScannerScopes ParserScopes)

set(
        SOURCES
        driver.cpp

        ${BISON_ParserScopes_OUTPUTS}
        ${FLEX_ScannerScopes_OUTPUTS}

        expressions/AndExpression.cpp
        expressions/IsEqualExpression.cpp
        expressions/IsGreaterExpression.cpp
        expressions/IsLessExpression.cpp
        expressions/ModuloExpression.cpp
        expressions/OrExpression.cpp
        expressions/NumberExpression.cpp
        expressions/MulExpression.cpp
        expressions/AddExpression.cpp
        expressions/SubtractExpression.cpp
        expressions/DivExpression.cpp
        expressions/IdentExpression.cpp
        expressions/ThisExpression.cpp
        expressions/FunctionCallExpression.cpp
        expressions/FunctionCallExpression.h

        statements/Statement.cpp
        statements/Assignment.cpp
        statements/AssignmentList.cpp
        statements/PrintStatement.cpp
        statements/ScopeAssignmentList.cpp
        statements/IfStatement.cpp
        statements/WhileStatement.cpp

        declarations/VarDecl.cpp
        declarations/DeclarationList.cpp
        declarations/MethodDecl.cpp
        declarations/ClassDecl.cpp

        visitors/Interpreter.cpp
        visitors/TemplateVisitor.h
        visitors/TemplateVisitor.cpp
        visitors/PrintVisitor.cpp
        visitors/TypeCheckerVisitor.cpp
        visitors/FunctionCallVisitor.cpp
        visitors/IrtreeBuildVisitor.h
        visitors/IrtreeBuildVisitor.cpp
        visitors/SymbolTreeVisitor.cpp

        symbol_table/Symbol.cpp
        symbol_table/Table.cpp
        symbol_table/ScopeLayer.cpp
        symbol_table/ScopeLayerTree.cpp
        objects/Integer.cpp
        objects/Object.cpp
        objects/UninitObject.cpp
        objects/Boolean.cpp
        objects/Class.cpp
        objects/Method.cpp

        Program.cpp

        main_class/MainClass.cpp

        functions/Function.cpp
        functions/ParamList.cpp
        functions/FunctionList.cpp
        functions/ParamValueList.cpp

        function-mechanisms/FrameEmulator.cpp
        function-mechanisms/FrameEmulator.h
        function-mechanisms/FunctionStorage.h
        function-mechanisms/FunctionStorage.cpp
        function-mechanisms/FunctionTable.h
        function-mechanisms/FunctionTable.cpp
        function-mechanisms/address/Address.h
        function-mechanisms/address/AddressInRegister.h
        function-mechanisms/address/AddressInRegister.cpp
        function-mechanisms/address/AddressInFrame.h
        function-mechanisms/address/AddressInFrame.cpp
        function-mechanisms/FrameTranslator.h
        function-mechanisms/FrameTranslator.cpp

        statements/ReturnStatement.cpp
        statements/ReturnStatement.h
)

add_subdirectory(irtree)

add_executable(
        MiniJavaCompiler
        main.cpp
        ${SOURCES}
)

add_executable(
        TestScopes
        tests/test_scope_layer.cpp
        ${SOURCES}
)

target_include_directories(
        TestScopes PRIVATE ${MiniJavaCompiler_SOURCE_DIR}
)

target_include_directories(
        MiniJavaCompiler PRIVATE ${MiniJavaCompiler_SOURCE_DIR}
)

target_link_libraries(MiniJavaCompiler ${IR_LIB})

add_custom_target(
        ScopesTree
        COMMAND dot -Tpng ${MiniJavaCompiler_SOURCE_DIR}/parser.gv -o ${MiniJavaCompiler_SOURCE_DIR}/parser.png

        DEPENDS ${MiniJavaCompiler_SOURCE_DIR}/parser.cpp
)

add_dependencies(MiniJavaCompiler ScopesTree)