#pragma once

#include <memory>

#include "ast/IExpression.hpp"
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
        std::any accept(IVisitor &visitor) const override;
        Tokens::Token unaryOperator;
        std::unique_ptr<IExpression>operand;
    };
}
