#pragma once

#include <any>
#include <memory>

#include "expressions/IExpression.hpp"

namespace Expression
{
    class GroupedExpression : public IExpression
    {
    public:
        GroupedExpression(std::unique_ptr<IExpression>&& groupedExpression);
        std::any accept(IExpressionVisitor &visitor) const override;
        std::unique_ptr<IExpression> groupedExpression;
    };
}
