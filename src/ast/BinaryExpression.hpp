#pragma once

#include <memory>

#include "ast/IExpression.hpp"
#include "tokens/Token.hpp"

namespace Expression
{
    class BinaryExpression : public IExpression
    {
    public:
        BinaryExpression(
            std::unique_ptr<IExpression>&& leftOperand,
            Tokens::Token binaryOperator,
            std::unique_ptr<IExpression>&& rightOperand
        );
        std::any accept(IVisitor& visitor) const override;
        std::unique_ptr<IExpression> leftOperand;
        Tokens::Token binaryOperator;
        std::unique_ptr<IExpression> rightOperand;
    };
}
