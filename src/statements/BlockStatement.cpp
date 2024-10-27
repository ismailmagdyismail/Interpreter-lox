#include "statements/BlockStatement.hpp"
#include "statements/IStatementVisitor.hpp"

using namespace Statement;

BlockStatement::BlockStatement(std::vector<std::unique_ptr<IStatement>>&& statements)
{
    this->statements = std::move(statements);
}

std::any BlockStatement::accept(IStatementVisitor &visitor) const
{
    return visitor.visitBlockStatement(*this);
}
