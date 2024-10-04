#include <algorithm>
#include <memory>

#include "ast/BinaryExpression.hpp"
#include "ast/IExpression.hpp"
#include "tokens/Token.hpp"
#include "ast/IVisitor.hpp"

using namespace Expression;

BinaryExpression::BinaryExpression(
    std::unique_ptr<IExpression>&& leftOperand,
    Tokens::Token binaryOperator,
    std::unique_ptr<IExpression>&& rightOperand
)
{
    this->leftOperand = std::move(leftOperand);
    this->binaryOperator = binaryOperator;
    this->rightOperand = std::move(rightOperand);
}

std::variant<std::string,std::monostate> BinaryExpression::accept(IVisitor& visitor) const
{
    return visitor.visitBinaryExpression(*this);
}
