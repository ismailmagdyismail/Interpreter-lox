#pragma once

#include "expressions/IExpression.hpp"
#include <memory>

namespace Expression
{
    class TernaryExpression : public IExpression
    {
    public:
        TernaryExpression(
            std::unique_ptr<IExpression>&& condition,
            std::unique_ptr<IExpression>&& trueExpression,
            std::unique_ptr<IExpression>&& falseExpression
        );
        std::any accept(IExpressionVisitor &visitor) const override;
        std::unique_ptr<IExpression> condition;
        std::unique_ptr<IExpression> trueExpression;
        std::unique_ptr<IExpression> falseExpression;
    };
}
