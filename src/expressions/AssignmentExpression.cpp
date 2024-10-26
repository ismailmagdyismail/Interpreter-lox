#include "expressions/AssignmentExpression.hpp"
#include "expressions/IExpressionVisitor.hpp"

using namespace Expression;

AssignmentExpression::AssignmentExpression(const Tokens::Token& token,std::unique_ptr<IExpression>&& value)
{
    this->idenetifier = token;
    this->value = std::move(value);
}

std::any AssignmentExpression::accept(IExpressionVisitor &visitor) const
{
    return visitor.visitAssignmentExpression(*this);
}
