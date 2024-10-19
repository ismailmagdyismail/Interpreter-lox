#pragma once

#include <any>
#include <iostream>
#include <variant>

namespace Expression {
    class BinaryExpression;
    class UnaryExpression;
    class LiteralExpression;
    class GroupedExpression;
    class TernaryExpression;
}

class IVisitor
{
public:
    /*
        - should be created with templates
        - BUT cannot mix dynamic, static polymorphism togther
    */
    virtual std::any visitBinaryExpression(const Expression::BinaryExpression& binaryExpression) = 0 ;
    virtual std::any visitUnaryExpression(const Expression::UnaryExpression& unaryExpression) = 0 ;
    virtual std::any visitLiteralExpression(const Expression::LiteralExpression& literalExpression) = 0 ;
    virtual std::any visitGroupedExpression(const Expression::GroupedExpression& groupedExpression) = 0 ;
    virtual std::any visitTernaryExpression(const Expression::TernaryExpression& ternaryExpression) = 0 ;

    virtual ~IVisitor() = default;
};
