#include <algorithm>
#include <memory>

#include "ast/GroupedExpression.hpp"
#include "ast/IExpression.hpp"
#include "ast/IVisitor.hpp"

using namespace Expression;

GroupedExpression::GroupedExpression(std::unique_ptr<IExpression>&& groupedExpression)
{
    this->groupedExpression = std::move(groupedExpression);
}

std::any GroupedExpression::accept(IVisitor &visitor) const
{
    return visitor.visitGroupedExpression(*this);
}
