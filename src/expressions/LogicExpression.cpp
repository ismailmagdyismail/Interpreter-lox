#include "expressions/LogicExpression.hpp"
#include "expressions/IExpressionVisitor.hpp"

using namespace Expression;

LogicExpression::LogicExpression(
    std::unique_ptr<IExpression>&& leftExpression,
    const Tokens::Token& logicalOperator,
    std::unique_ptr<IExpression>&& rightExpression
)
{
    this->leftExpression = std::move(leftExpression);
    this->logicalOperator = logicalOperator;
    this->rightExpression = std::move(rightExpression);
}

std::any LogicExpression::accept(IExpressionVisitor& visitor) const
{
    return visitor.visitLogicExpression(*this);
}
