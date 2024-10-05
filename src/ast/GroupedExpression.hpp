#pragma once

#include <any>
#include <memory>

#include "ast/IExpression.hpp"

namespace Expression
{
    class GroupedExpression : public IExpression
    {
    public:
        GroupedExpression(std::unique_ptr<IExpression>&& groupedExpression);
        std::any accept(IVisitor &visitor) const override;
        std::unique_ptr<IExpression> groupedExpression;
    };
}
