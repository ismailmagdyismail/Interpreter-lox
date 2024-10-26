#include <memory>

#include "statements/PrintStatement.hpp"
#include "statements/IStatementVisitor.hpp"

using namespace Statement;

PrintStatement::PrintStatement(std::unique_ptr<Expression::IExpression>&& expression)
{
    this->expression = std::move(expression);
}

std::any PrintStatement::accept(IStatementVisitor &visitor) const
{
    return visitor.visitPrintStatement(*this);
}
