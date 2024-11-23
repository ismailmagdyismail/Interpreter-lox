#pragma once

#include "expressions/IExpression.hpp"
#include "tokens/Token.hpp"

class IExpressionVisitor;

namespace Expression
{
    class LogicExpression : public IExpression
    {
    public:
        LogicExpression(
            std::unique_ptr<IExpression>&& leftExpression,
            const Tokens::Token& logicalOperator,
            std::unique_ptr<IExpression>&& rightExpression
        );
        std::any accept(IExpressionVisitor& visitor) const override;
        std::unique_ptr<IExpression> leftExpression;
        Tokens::Token logicalOperator;
        std::unique_ptr<IExpression> rightExpression;
    };
}
