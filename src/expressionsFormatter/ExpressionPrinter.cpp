#include <any>
#include <iostream>
#include <variant>

#include "expressions/LiteralExpression.hpp"
#include "expressions/VariableExpression.hpp"
#include "expressionsFormatter/ExpressionPrinter.hpp"
#include "expressions/UnaryExpression.hpp"
#include "expressions/BinaryExpression.hpp"
#include "expressions/GroupedExpression.hpp"
#include "expressions/TernaryExpression.hpp"
#include "expressions/AssignmentExpression.hpp"
#include "stringBuilder/StringBuilder.hpp"
#include "object/Object.hpp"


std::any ExpressionPrinter::visitBinaryExpression(const Expression::BinaryExpression &binaryExpression)
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

std::any ExpressionPrinter::visitUnaryExpression(const Expression::UnaryExpression &unaryExpression)
{
    return StringBuilder()
        .add("(")
        .add(unaryExpression.unaryOperator.lexeme)
        .add(Object::toString(unaryExpression.operand->accept(*this)))
        .add(")")
        .build();
}


std::any ExpressionPrinter::visitGroupedExpression(const Expression::GroupedExpression &groupedExpression)
{
    return StringBuilder()
            .add("(")
            .add(Object::toString(groupedExpression.groupedExpression->accept(*this)))
            .add(")")
            .build();
}

std::any ExpressionPrinter::visitLiteralExpression(const Expression::LiteralExpression &literalExpression)
{
    return StringBuilder()
           .add(Object::toString(literalExpression.value))
           .build();
}

std::any ExpressionPrinter::visitTernaryExpression(const Expression::TernaryExpression &ternaryExpression)
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


std::any ExpressionPrinter::visitVariableExpression(const Expression::VariableExpression &variableExpression)
{
    return StringBuilder()
           .add("(")
           .add(variableExpression.identifer.lexeme)
           .add(")")
           .build();
}

std::any ExpressionPrinter::visitAssignmentExpression(const Expression::AssignmentExpression &assignmentExpression)
{
    std::string value = Object::toString(assignmentExpression.accept(*this));
    return StringBuilder()
           .add("(")
           .add(assignmentExpression.idenetifier.lexeme)
           .add("=")
           .add(value)
           .add(")")
           .build();
}
