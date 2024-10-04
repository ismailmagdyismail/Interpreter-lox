#include "ast/LiteralExpression.hpp"
#include "ast/IVisitor.hpp"
#include <any>

using namespace Expression;

LiteralExpression::LiteralExpression(std::any value) : value(value){}

std::variant<std::string,std::monostate> LiteralExpression::accept(IVisitor &visitor) const
{
    return visitor.visitLiteralExpression(*this);
}
