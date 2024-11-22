#include "statements/IfStatement.hpp"
#include "statements/IStatementVisitor.hpp"

using namespace Statement;

IfStatement::IfStatement(
    std::unique_ptr<Expression::IExpression>&& condition,
    std::unique_ptr<IStatement>&& trueBranchStatements,
    std::unique_ptr<IStatement>&& falseBranchStatements
)
{
    this->condition = std::move(condition);
    this->trueBranchStatements = std::move(trueBranchStatements);
    this->falseBranchStatements = std::move(falseBranchStatements);
}

std::any IfStatement::accept(IStatementVisitor& visitor) const
{
    return visitor.visitIfStatement(*this);
}
