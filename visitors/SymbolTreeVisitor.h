#include "TemplateVisitor.h"

#include "symbol_table/Table.h"
#include <map>

#include "symbol_table/ScopeLayerTree.h"

class SymbolTreeVisitor : public Visitor {
 public:
  SymbolTreeVisitor();
  ~SymbolTreeVisitor() = default;
  void Visit(NumberExpression* expression) override;
  void Visit(AddExpression* expression) override;
  void Visit(SubtractExpression* expression) override;
  void Visit(MulExpression* expression) override;
  void Visit(DivExpression* expression) override;
  void Visit(IdentExpression* expression) override;
  void Visit(PrintStatement* statement) override;
  void Visit(Assignment* assignment) override;
  void Visit(VarDecl* var_decl) override;
  void Visit(AssignmentList* assignment_list) override;
  void Visit(ScopeAssignmentList* list) override;
  void Visit(Program* program) override;

  void Visit(AndExpression* expression) override;
  void Visit(IsEqualExpression* expression) override;
  void Visit(IsGreaterExpression* expression) override;
  void Visit(IsLessExpression* expression) override;
  void Visit(ModuloExpression* expression) override;
  void Visit(OrExpression* expression) override;
  void Visit(IfStatement* if_statement) override;
  void Visit(WhileStatement* while_statement) override;

  ScopeLayer* GetRoot();
 private:
  ScopeLayerTree tree_;
  ScopeLayer* current_layer_;
};