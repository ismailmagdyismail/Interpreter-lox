#include "ast/LiteralExpression.hpp"
#include "ast/IVisitor.hpp"
#include <any>

using namespace Expression;

LiteralExpression::LiteralExpression(std::any value) : value(value){}

std::any LiteralExpression::accept(IVisitor &visitor) const
{
    return visitor.visitLiteralExpression(*this);
}
