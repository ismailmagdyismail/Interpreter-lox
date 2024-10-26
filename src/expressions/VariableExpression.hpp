#pragma once

#include "expressions/IExpression.hpp"
#include "tokens/Token.hpp"

namespace Expression
{
    class VariableExpression : public IExpression
    {
    public:
        VariableExpression(const Tokens::Token token);
        std::any accept(IExpressionVisitor &visitor) const override;
        Tokens::Token identifer;
    };
}
