#pragma once

#include "expressions/IExpression.hpp"
#include "expressions/IExpressionVisitor.hpp"
#include "sourceReporter/SourceReporter.hpp"
#include <any>
#include <memory>

class Interpreter : IExpressionVisitor
{
public:
    std::any interpret(const std::unique_ptr<Expression::IExpression>& expression,SourceReport::SourceReporter& reporter);
private:
    std::any visitUnaryExpression(const Expression::UnaryExpression &unaryExpression) override;
    std::any visitBinaryExpression(const Expression::BinaryExpression &binaryExpression) override;
    std::any visitGroupedExpression(const Expression::GroupedExpression &groupedExpression) override;
    std::any visitLiteralExpression(const Expression::LiteralExpression &literalExpression) override;
    std::any visitTernaryExpression(const Expression::TernaryExpression &ternaryExpression) override;
};
