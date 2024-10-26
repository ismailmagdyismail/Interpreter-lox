#pragma once

#include <memory>

#include "expressions/IExpression.hpp"
#include "tokens/Token.hpp"

namespace Expression
{
    class AssignmentExpression : public IExpression
    {
    public:
        AssignmentExpression(const Tokens::Token& token,std::unique_ptr<IExpression>&& value);
        std::any accept(IExpressionVisitor &visitor) const override;
        Tokens::Token idenetifier;
        std::unique_ptr<IExpression> value;
    };
}
