#include "ast/TernaryExpression.hpp"
#include "ast/IVisitor.hpp"

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

std::any TernaryExpression::accept(IVisitor &visitor) const
{
    return visitor.visitTernaryExpression(*this);
}
