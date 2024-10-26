#pragma once

#include "expressions/IExpression.hpp"
#include "statements/IStatement.hpp"
#include <memory>

namespace Statement
{
    class ExpressionStatement : public IStatement
    {
    public:
        ExpressionStatement(std::unique_ptr<Expression::IExpression>&& expression);
        std::any accept(IStatementVisitor &visitor) const override;
        std::unique_ptr<Expression::IExpression> expression;
    };
}
