
//! statements
#include "statements/ForStatement.hpp"
#include "statements/IStatementVisitor.hpp"

using namespace Statement;

ForStatement::ForStatement(
    std::unique_ptr<IStatement>&& initialization,
    std::unique_ptr<Expression::IExpression>&& condition,
    std::unique_ptr<Expression::IExpression>&& increment,
    std::unique_ptr<IStatement>&& loopBody
)
{
    this->condition = std::move(condition);
    this->increment = std::move(increment);
    this->initialization = std::move(initialization);
    this->loopBody = std::move(loopBody);
}

std::any ForStatement::accept(IStatementVisitor& visitor) const
{
    return visitor.visitForStatement(*this);
}
