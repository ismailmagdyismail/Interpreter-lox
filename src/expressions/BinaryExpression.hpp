#pragma once

#include <memory>

#include "expressions/IExpression.hpp"
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
        std::any accept(IExpressionVisitor& visitor) const override;
        std::unique_ptr<IExpression> leftOperand;
        Tokens::Token binaryOperator;
        std::unique_ptr<IExpression> rightOperand;
    };
}
