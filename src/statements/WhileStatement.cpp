#include "statements/WhileStatement.hpp"
#include "statements/IStatementVisitor.hpp"

using namespace Statement;

WhileStatement::WhileStatement(std::unique_ptr<Expression::IExpression>&& condition, std::unique_ptr<IStatement>&& loopBody)
{
    this->condition = std::move(condition);
    this->loopBody = std::move(loopBody);
}

std::any WhileStatement::accept(IStatementVisitor& visitor)const
{
    return visitor.visitWhileStatement(*this);
}
