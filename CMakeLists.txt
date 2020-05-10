project(MiniJavaCompiler)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

include_directories(
        scanner
        driver
        expressions
        assignments
        base
        visitors
        .
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MiniJavaCompiler_SOURCE_DIR}/bin)

set(
        HEADERS
        ${MiniJavaCompiler_SOURCE_DIR}/driver/driver.h
        ${MiniJavaCompiler_SOURCE_DIR}/parser.hh
)

BISON_TARGET(
        Parser
        parser.y
        ${MiniJavaCompiler_SOURCE_DIR}/parser.cpp
        DEFINES_FILE ${MiniJavaCompiler_SOURCE_DIR}/parser.hh
)

FLEX_TARGET(
        Scanner
        scanner.l
        ${MiniJavaCompiler_SOURCE_DIR}/scanner/scanner.cpp
)

add_executable(
        MiniJavaCompiler
        main.cpp
        driver/driver.cpp
        expressions/AddExpression.cpp
        expressions/MulExpression.cpp
        expressions/DivExpression.cpp
        expressions/SubtractExpression.cpp
        expressions/NumberExpression.cpp
        expressions/IdentExpression.cpp
        assignments/Assignment.cpp
        ${BISON_Parser_OUTPUTS}
        ${FLEX_Scanner_OUTPUTS}
        assignments/AssignmentList.cpp
        assignments/AssignmentList.h
        expressions/Expression.h
        Program.cpp Program.h
        visitors/Visitor.h
        base/BaseElement.h
        visitors/Interpreter.cpp
        visitors/Interpreter.h
        visitors/PrintVisitor.cpp
        visitors/PrintVisitor.h
)

target_include_directories(MiniJavaCompiler PRIVATE ${MiniJavaCompiler_SOURCE_DIR})
