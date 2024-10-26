#include <algorithm>
#include <memory>

#include "expressions/GroupedExpression.hpp"
#include "expressions/IExpression.hpp"
#include "expressions/IExpressionVisitor.hpp"

using namespace Expression;

GroupedExpression::GroupedExpression(std::unique_ptr<IExpression>&& groupedExpression)
{
    this->groupedExpression = std::move(groupedExpression);
}

std::any GroupedExpression::accept(IExpressionVisitor &visitor) const
{
    return visitor.visitGroupedExpression(*this);
}
