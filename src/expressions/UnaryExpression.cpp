#include <memory>
#include <utility>
#include <variant>

#include "expressions/UnaryExpression.hpp"
#include "expressions/IExpression.hpp"
#include "expressions/IExpressionVisitor.hpp"

using namespace Expression;

UnaryExpression::UnaryExpression(Tokens::Token unaryOperator,std::unique_ptr<IExpression>&& expression)
{
    this->unaryOperator = unaryOperator;
    this->operand = std::move(expression);
}

std::any UnaryExpression::accept(IExpressionVisitor &visitor) const
{
    return visitor.visitUnaryExpression(*this);
}
