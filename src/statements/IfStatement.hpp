#pragma once

// system includes
#include <memory>

#include "expressions/IExpression.hpp"
#include "statements/IStatement.hpp"

class IStatementVisitor;

namespace Statement
{
    class IfStatement : public IStatement
    {
    public:
        IfStatement(
            std::unique_ptr<Expression::IExpression>&& condition,
            std::unique_ptr<IStatement>&& trueBranchStatements,
            std::unique_ptr<IStatement>&& falseBranchStatements = nullptr
        );
        std::any accept(IStatementVisitor &visitor) const override;
        std::unique_ptr<Expression::IExpression> condition;
        std::unique_ptr<Statement::IStatement> trueBranchStatements;
        std::unique_ptr<Statement::IStatement>falseBranchStatements;
    };
}
