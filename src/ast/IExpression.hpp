#pragma once

#include <variant>

class IVisitor;

namespace Expression
{
    class IExpression
    {
    public:
        virtual std::variant<std::string,std::monostate> accept(IVisitor& visitor) const = 0;
        virtual ~IExpression() = default;
    };
}
