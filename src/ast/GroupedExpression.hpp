#pragma once

#include <memory>

#include "ast/IExpression.hpp"

namespace Expression
{
    class GroupedExpression : public IExpression
    {
    public:
        GroupedExpression(std::unique_ptr<IExpression>&& groupedExpression);
        std::variant<std::string,std::monostate> accept(IVisitor &visitor) const override;
        std::unique_ptr<IExpression> groupedExpression;
    };
}
