#pragma once

//! statements
#include "statements/IStatement.hpp"

//! expressions
#include "expressions/IExpression.hpp"

class IStatementVisitor;

namespace Statement
{
    class ForStatement: public IStatement
    {
    public:
        ForStatement(
            std::unique_ptr<IStatement>&& initialization,
            std::unique_ptr<Expression::IExpression>&& condition,
            std::unique_ptr<Expression::IExpression>&& increment,
            std::unique_ptr<IStatement>&& loopBody
        );
        std::any accept(IStatementVisitor& visitor) const override;
        std::unique_ptr<IStatement> initialization;
        std::unique_ptr<Expression::IExpression> condition;
        std::unique_ptr<Expression::IExpression> increment;
        std::unique_ptr<IStatement> loopBody;

    };
}
