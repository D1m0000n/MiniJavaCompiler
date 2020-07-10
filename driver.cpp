#include "include/driver.hh"
#include "parser.hh"

#include "visitors/Interpreter.h"
#include "visitors/PrintVisitor.h"
#include "visitors/SymbolTreeVisitor.h"
#include "visitors/TypeCheckerVisitor.h"
#include "visitors/FunctionCallVisitor.h"

Driver::Driver() :
    trace_parsing(false),
    trace_scanning(false),
    scanner(*this), parser(scanner, *this) {
}

int Driver::parse(const std::string& f) {
  file = f;
  location.initialize(&file);
  scan_begin();
  parser.set_debug_level(trace_parsing);
  int res = parser();
  std::cout << "parser " << res << std::endl;
  scan_end();
  return res;
}

void Driver::Evaluate() {
  SymbolTreeVisitor visitor;
  try {
    visitor.Visit(program);
  } catch (std::runtime_error& error) {
    std::cout << error.what() << std::endl;
    exit(1);
  }
  std::cout << "Symbol tree built" << std::endl;

  ScopeLayer* root = visitor.GetRoot();

  TypeCheckerVisitor type_checker(root);
  try{
    type_checker.CheckTypes(program);
  } catch (std::runtime_error& error) {
    std::cout << error.what() << std::endl;
    exit(1);
  }
  std::cout << "Types checked" << std::endl;

  Interpreter interpreter(root);
  interpreter.GetResult(program);
}

void Driver::scan_begin() {
  scanner.set_debug(trace_scanning);
  if (file.empty() || file == "-") {
  } else {
    stream.open(file);
    std::cout << file << std::endl;
    scanner.yyrestart(&stream);
  }
}

void Driver::scan_end() {
  stream.close();
}

void Driver::PrintTree(const std::string& filename) {
  PrintVisitor visitor(filename);
  visitor.Visit(program);
}

