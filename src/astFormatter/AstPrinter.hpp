#pragma once

#include "ast/IVisitor.hpp"
#include <memory>

class AstPrinter : public IVisitor
{
public:
    std::variant<std::string, std::monostate> visitBinaryExpression(const Expression::BinaryExpression &binaryExpression) override;
    std::variant<std::string, std::monostate> visitUnaryExpression(const Expression::UnaryExpression &unaryExpression) override;
    std::variant<std::string, std::monostate> visitGroupedExpression(const Expression::GroupedExpression &groupedExpression) override;
    std::variant<std::string, std::monostate> visitLiteralExpression(const Expression::LiteralExpression &literalExpression) override;
private:
};
