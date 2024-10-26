#include "statements/VarStatement.hpp"
#include "statements/IStatementVisitor.hpp"

using namespace Statement;

VarStatement::VarStatement(const Tokens::Token& token,std::unique_ptr<Expression::IExpression>&& value)
{
    this->identifier = token;
    this->value = std::move(value);
}

std::any VarStatement::accept(IStatementVisitor &visitor) const
{
    return visitor.visitVarStatement(*this);
}
