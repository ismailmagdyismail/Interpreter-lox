#pragma once

#include <any>
#include <variant>

class IExpressionVisitor;

namespace Expression
{
    class IExpression
    {
    public:
        virtual std::any accept(IExpressionVisitor& visitor) const = 0;
        virtual ~IExpression() = default;
    };
}
