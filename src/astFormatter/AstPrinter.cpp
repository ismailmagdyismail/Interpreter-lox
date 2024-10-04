#include <iostream>
#include <variant>

#include "ast/LiteralExpression.hpp"
#include "astFormatter/AstPrinter.hpp"
#include "ast/UnaryExpression.hpp"
#include "ast/BinaryExpression.hpp"
#include "ast/GroupedExpression.hpp"
#include "stringBuilder/StringBuilder.hpp"
#include "utils/GenericType.hpp"


std::variant<std::string,std::monostate> AstPrinter::visitBinaryExpression(const Expression::BinaryExpression &binaryExpression)
{
    return StringBuilder()
            .add("(")
            .add(std::get<std::string>(binaryExpression.leftOperand->accept(*this)))
            .add(binaryExpression.binaryOperator.lexeme)
            .add(std::get<std::string>(binaryExpression.rightOperand->accept(*this)))
            .add(")")
            .build();
}

std::variant<std::string,std::monostate> AstPrinter::visitUnaryExpression(const Expression::UnaryExpression &unaryExpression)
{
    return StringBuilder()
        .add("(")
        .add(unaryExpression.unaryOperator.lexeme)
        .add(std::get<std::string>(unaryExpression.operand->accept(*this)))
        .add(")")
        .build();
}


std::variant<std::string,std::monostate> AstPrinter::visitGroupedExpression(const Expression::GroupedExpression &groupedExpression)
{
    return StringBuilder()
            .add("(")
            .add(std::get<std::string>(groupedExpression.groupedExpression->accept(*this)))
            .add(")")
            .build();
}

std::variant<std::string,std::monostate> AstPrinter::visitLiteralExpression(const Expression::LiteralExpression &literalExpression)
{
    return StringBuilder()
           .add(GenericType::toString(literalExpression.value))
           .build();
}
