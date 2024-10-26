#pragma once

#include "expressions/IExpression.hpp"
#include "statements/IStatement.hpp"
#include <any>
#include <memory>

namespace Statement
{
    class PrintStatement: public IStatement
    {
    public:
        PrintStatement(std::unique_ptr<Expression::IExpression>&& expression);
        std::any accept(IStatementVisitor &visitor) const override;
        std::unique_ptr<Expression::IExpression> expression;
    };
}
