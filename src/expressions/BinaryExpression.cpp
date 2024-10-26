#include <algorithm>
#include <memory>

#include "expressions/BinaryExpression.hpp"
#include "expressions/IExpression.hpp"
#include "tokens/Token.hpp"
#include "expressions/IExpressionVisitor.hpp"

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

std::any BinaryExpression::accept(IExpressionVisitor& visitor) const
{
    return visitor.visitBinaryExpression(*this);
}
