#include "include/driver.hh"
#include "parser.hh"

#include "visitors/Interpreter.h"
#include "visitors/PrintVisitor.h"
#include "visitors/SymbolTreeVisitor.h"
#include "visitors/TypeCheckerVisitor.h"
#include "visitors/FunctionCallVisitor.h"
#include <visitors/IrtreeBuildVisitor.h>

#include <function-mechanisms/FunctionStorage.h>

#include <irtree/visitors/PrintVisitor.h>


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

  ScopeLayerTree root = visitor.GetRoot();

  auto methods = visitor.GetFunctions();
  FunctionStorage& storage = FunctionStorage::GetInstance();
  for (auto it : methods) {
    storage.Set(it.first, it.second);
  }

  TypeCheckerVisitor type_checker(&root);
  try {
    type_checker.CheckTypes(program);
  } catch (std::runtime_error& error) {
    std::cout << error.what() << std::endl;
    exit(1);
  }
  std::cout << "Types checked" << std::endl;


  std::string main_func_name = program->main_class_->identifier + "." + "main";
  Function* main_function = storage.Get(Symbol(main_func_name));
  std::shared_ptr<Method> method_type = std::dynamic_pointer_cast<Method>(
      root.Get(Symbol(main_func_name))
  );

  FunctionCallVisitor function_visitor(
      root.GetFunctionScopeByName(Symbol(main_func_name)),
      method_type
  );
  function_visitor.SetTree(&root);
  function_visitor.SetThis(program->main_class_->identifier);
  function_visitor.Visit(main_function);

  root.PrintTree("ir_test_dir/symbol_tree.txt");

  IrtreeBuildVisitor irt_build_visitor(&root);
  irt_build_visitor.SetMainFunction(main_function);
  irt_build_visitor.Visit(program);

  IrtMapping irt_methods = irt_build_visitor.GetTrees();

  for (auto func_view = irt_methods.begin(); func_view != irt_methods.end(); ++func_view) {
    IRT::PrintVisitor print_visitor_irt("ir_test_dir/" + func_view->first + "_irt.txt");
    irt_methods[func_view->first]->Accept(&print_visitor_irt);
  }
//  Interpreter interpreter(root);
//  interpreter.GetResult(program);
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

