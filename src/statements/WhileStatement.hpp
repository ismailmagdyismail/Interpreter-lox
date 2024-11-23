#pragma once

//system includes
#include <memory>

#include "statements/IStatement.hpp"
#include "expressions/IExpression.hpp"

class IStatementVisitor;

namespace Statement
{
    class WhileStatement : public IStatement
    {
    public:
        WhileStatement(std::unique_ptr<Expression::IExpression>&& condition, std::unique_ptr<IStatement>&& loopBody);
        std::any accept(IStatementVisitor& visitor)const override;
        std::unique_ptr<Expression::IExpression> condition;
        std::unique_ptr<IStatement>loopBody;
    };
}
