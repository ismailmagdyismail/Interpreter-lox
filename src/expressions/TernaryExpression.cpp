#include "expressions/TernaryExpression.hpp"
#include "expressions/IExpressionVisitor.hpp"

using namespace Expression;

TernaryExpression::TernaryExpression(
    std::unique_ptr<IExpression>&& condition,
    std::unique_ptr<IExpression>&& trueExpression,
    std::unique_ptr<IExpression>&& falseExpression
)
{
    this->condition = std::move(condition);
    this->trueExpression = std::move(trueExpression);
    this->falseExpression = std::move(falseExpression);
}

std::any TernaryExpression::accept(IExpressionVisitor &visitor) const
{
    return visitor.visitTernaryExpression(*this);
}
