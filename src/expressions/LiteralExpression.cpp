#include "expressions/LiteralExpression.hpp"
#include "expressions/IExpressionVisitor.hpp"
#include <any>

using namespace Expression;

LiteralExpression::LiteralExpression(std::any value) : value(value){}

std::any LiteralExpression::accept(IExpressionVisitor &visitor) const
{
    return visitor.visitLiteralExpression(*this);
}
