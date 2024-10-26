#include "statements/ExpressionStatement.hpp"
#include "statements/IStatementVisitor.hpp"

using namespace Statement;

ExpressionStatement::ExpressionStatement(std::unique_ptr<Expression::IExpression>&& expression)
{
    this->expression = std::move(expression);
}

std::any ExpressionStatement::accept(IStatementVisitor& visitor) const
{
    return visitor.visitExpressionStatement(*this);
}
