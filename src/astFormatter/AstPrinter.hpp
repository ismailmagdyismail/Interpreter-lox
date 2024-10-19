#pragma once

#include "ast/IVisitor.hpp"
#include <memory>

class AstPrinter : public IVisitor
{
public:
    std::any visitBinaryExpression(const Expression::BinaryExpression &binaryExpression) override;
    std::any visitUnaryExpression(const Expression::UnaryExpression &unaryExpression) override;
    std::any visitGroupedExpression(const Expression::GroupedExpression &groupedExpression) override;
    std::any visitLiteralExpression(const Expression::LiteralExpression &literalExpression) override;
    std::any visitTernaryExpression(const Expression::TernaryExpression &ternaryExpression) override;
private:
};
