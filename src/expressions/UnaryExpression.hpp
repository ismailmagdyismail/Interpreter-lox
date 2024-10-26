#pragma once

#include <memory>

#include "expressions/IExpression.hpp"
#include "tokens/Token.hpp"

namespace Expression
{
    class UnaryExpression final : public IExpression
    {
    public:
        UnaryExpression(
            Tokens::Token unaryOperator,
            std::unique_ptr<IExpression>&& expression
        );
        std::any accept(IExpressionVisitor &visitor) const override;
        Tokens::Token unaryOperator;
        std::unique_ptr<IExpression>operand;
    };
}
