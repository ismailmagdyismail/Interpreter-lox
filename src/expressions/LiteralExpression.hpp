#pragma once

#include "expressions/IExpression.hpp"
#include <any>

namespace Expression
{
    class LiteralExpression : public IExpression
    {
    public:
        LiteralExpression(std::any value);
        std::any accept(IExpressionVisitor &visitor) const override;
        std::any value;
    };
}
