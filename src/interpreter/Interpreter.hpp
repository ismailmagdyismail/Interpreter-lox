#pragma once

#include <any>
#include <memory>


#include "enviroment/Enviroment.hpp"
#include "expressions/AssignmentExpression.hpp"
#include "expressions/IExpression.hpp"
#include "expressions/IExpressionVisitor.hpp"
#include "sourceReporter/SourceReporter.hpp"
#include "statements/IStatement.hpp"
#include "statements/IStatementVisitor.hpp"

class Interpreter : IExpressionVisitor , IStatementVisitor
{
public:
    void interpret(const std::vector<std::unique_ptr<Statement::IStatement>>& statements,SourceReport::SourceReporter& reporter);
private:
    std::any visitUnaryExpression(const Expression::UnaryExpression &unaryExpression) override;
    std::any visitBinaryExpression(const Expression::BinaryExpression &binaryExpression) override;
    std::any visitGroupedExpression(const Expression::GroupedExpression &groupedExpression) override;
    std::any visitLiteralExpression(const Expression::LiteralExpression &literalExpression) override;
    std::any visitTernaryExpression(const Expression::TernaryExpression &ternaryExpression) override;
    std::any visitVariableExpression(const Expression::VariableExpression &variableExpression) override;
    std::any visitAssignmentExpression(const Expression::AssignmentExpression &assignmentExpression) override;

    std::any visitExpressionStatement(const Statement::ExpressionStatement& expressionStatement) override;
    std::any visitPrintStatement(const Statement::PrintStatement &printStatement) override;
    std::any visitVarStatement(const Statement::VarStatement &) override;
    std::any visitBlockStatement(const Statement::BlockStatement &) override;

    Environment environment;
};
