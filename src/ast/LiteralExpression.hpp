#pragma once

#include "ast/IExpression.hpp"
#include <any>

namespace Expression
{
    class LiteralExpression : public IExpression
    {
    public:
        LiteralExpression(std::any value);
        std::any accept(IVisitor &visitor) const override;
        std::any value;
    };
}
