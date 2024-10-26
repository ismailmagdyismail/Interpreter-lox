#include <any>

#include "expressions/VariableExpression.hpp"
#include "expressions/IExpressionVisitor.hpp"


using namespace Expression;

VariableExpression::VariableExpression(const Tokens::Token identifer):identifer(identifer){}

std::any VariableExpression::accept(IExpressionVisitor &visitor) const
{
    return visitor.visitVariableExpression(*this);
}
