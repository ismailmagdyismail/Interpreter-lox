#include <any>
#include <iostream>
#include <variant>

#include "ast/LiteralExpression.hpp"
#include "astFormatter/AstPrinter.hpp"
#include "ast/UnaryExpression.hpp"
#include "ast/BinaryExpression.hpp"
#include "ast/GroupedExpression.hpp"
#include "ast/TernaryExpression.hpp"
#include "stringBuilder/StringBuilder.hpp"
#include "object/Object.hpp"


std::any AstPrinter::visitBinaryExpression(const Expression::BinaryExpression &binaryExpression)
{
    auto leftOperand  = Object::toString(binaryExpression.leftOperand->accept(*this));
    auto rightOperand  = Object::toString(binaryExpression.rightOperand->accept(*this));
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
        .add(Object::toString(unaryExpression.operand->accept(*this)))
        .add(")")
        .build();
}


std::any AstPrinter::visitGroupedExpression(const Expression::GroupedExpression &groupedExpression)
{
    return StringBuilder()
            .add("(")
            .add(Object::toString(groupedExpression.groupedExpression->accept(*this)))
            .add(")")
            .build();
}

std::any AstPrinter::visitLiteralExpression(const Expression::LiteralExpression &literalExpression)
{
    return StringBuilder()
           .add(Object::toString(literalExpression.value))
           .build();
}

std::any AstPrinter::visitTernaryExpression(const Expression::TernaryExpression &ternaryExpression)
{
    std::any condition = ternaryExpression.condition->accept(*this);
    std::any trueExpression = ternaryExpression.trueExpression->accept(*this);
    std::any falseExpression = ternaryExpression.falseExpression->accept(*this);

    return StringBuilder()
           .add("(")
           .add(Object::toString(condition))
           .add(")")
           .add("?") // leaky abstration , coupled to the fact that ternary is only ?: . but easy to solve
           .add("(")
           .add(Object::toString(trueExpression))
           .add(")")
           .add(":")// leaky abstration , coupled to the fact that ternary is only ?: . but easy to solve
           .add("(")
           .add(Object::toString(falseExpression))
           .add(")")
           .build();
}
