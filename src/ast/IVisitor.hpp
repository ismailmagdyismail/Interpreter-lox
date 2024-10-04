#pragma once

#include <iostream>
#include <variant>

namespace Expression {
    class BinaryExpression;
    class UnaryExpression;
    class LiteralExpression;
    class GroupedExpression;
}

class IVisitor
{
public:
    /*
        - should be created with templates
        - BUT cannot mix dynamic, static polymorphism togther
    */
    virtual std::variant<std::string,std::monostate> visitBinaryExpression(const Expression::BinaryExpression& binaryExpression) = 0 ;
    virtual std::variant<std::string,std::monostate> visitUnaryExpression(const Expression::UnaryExpression& unaryExpression) = 0 ;
    virtual std::variant<std::string,std::monostate> visitLiteralExpression(const Expression::LiteralExpression& literalExpression) = 0 ;
    virtual std::variant<std::string,std::monostate> visitGroupedExpression(const Expression::GroupedExpression& groupedExpression) = 0 ;
    virtual ~IVisitor() = default;
};
