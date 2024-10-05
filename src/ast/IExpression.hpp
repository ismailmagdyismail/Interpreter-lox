#pragma once

#include <any>
#include <variant>

class IVisitor;

namespace Expression
{
    class IExpression
    {
    public:
        virtual std::any accept(IVisitor& visitor) const = 0;
        virtual ~IExpression() = default;
    };
}
