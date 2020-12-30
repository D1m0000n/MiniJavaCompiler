#include <Expression.h>

class ThisExpression : public Expression {
 public:
  ThisExpression() = default;
  void Accept(Visitor* visitor) override;
};
