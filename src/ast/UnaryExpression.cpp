#include <memory>
#include <utility>
#include <variant>

#include "ast/UnaryExpression.hpp"
#include "ast/IExpression.hpp"
#include "ast/IVisitor.hpp"

using namespace Expression;

UnaryExpression::UnaryExpression(Tokens::Token unaryOperator,std::unique_ptr<IExpression>&& expression)
{
    this->unaryOperator = unaryOperator;
    this->operand = std::move(expression);
}

std::any UnaryExpression::accept(IVisitor &visitor) const
{
    return visitor.visitUnaryExpression(*this);
}
