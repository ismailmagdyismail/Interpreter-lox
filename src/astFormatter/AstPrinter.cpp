#include <iostream>
#include <variant>

#include "ast/LiteralExpression.hpp"
#include "astFormatter/AstPrinter.hpp"
#include "ast/UnaryExpression.hpp"
#include "ast/BinaryExpression.hpp"
#include "ast/GroupedExpression.hpp"
#include "stringBuilder/StringBuilder.hpp"
#include "utils/GenericType.hpp"


std::any AstPrinter::visitBinaryExpression(const Expression::BinaryExpression &binaryExpression)
{
    auto leftOperand  = GenericType::toString(binaryExpression.leftOperand->accept(*this));
    auto rightOperand  = GenericType::toString(binaryExpression.rightOperand->accept(*this));
    return StringBuilder()
            .add("(")
            .add(leftOperand)
            .add(binaryExpression.binaryOperator.lexeme)
            .add(rightOperand)
            .add(")")
            .build();
}

std::any AstPrinter::visitUnaryExpression(const Expression::UnaryExpression &unaryExpression)
{
    return StringBuilder()
        .add("(")
        .add(unaryExpression.unaryOperator.lexeme)
        .add(GenericType::toString(unaryExpression.operand->accept(*this)))
        .add(")")
        .build();
}


std::any AstPrinter::visitGroupedExpression(const Expression::GroupedExpression &groupedExpression)
{
    return StringBuilder()
            .add("(")
            .add(GenericType::toString(groupedExpression.groupedExpression->accept(*this)))
            .add(")")
            .build();
}

std::any AstPrinter::visitLiteralExpression(const Expression::LiteralExpression &literalExpression)
{
    return StringBuilder()
           .add(GenericType::toString(literalExpression.value))
           .build();
}
