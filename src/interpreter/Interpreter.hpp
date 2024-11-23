#pragma once

#include <any>
#include <memory>


//! environment
#include "enviroment/Enviroment.hpp"
#include "enviroment/EnviromentManager.hpp"


//! expressions
#include "expressions/IExpression.hpp"
#include "expressions/IExpressionVisitor.hpp"

//! reporter
#include "sourceReporter/SourceReporter.hpp"

//! statements
#include "statements/IStatement.hpp"
#include "statements/IStatementVisitor.hpp"

class Interpreter : public IExpressionVisitor , public IStatementVisitor
{
public:
    void interpret(const std::vector<std::unique_ptr<Statement::IStatement>>& statements,SourceReport::SourceReporter& reporter);
private:
    // expression nodes visitors
    std::any visitUnaryExpression(const Expression::UnaryExpression &unaryExpression) override;
    std::any visitBinaryExpression(const Expression::BinaryExpression &binaryExpression) override;
    std::any visitGroupedExpression(const Expression::GroupedExpression &groupedExpression) override;
    std::any visitLiteralExpression(const Expression::LiteralExpression &literalExpression) override;
    std::any visitTernaryExpression(const Expression::TernaryExpression &ternaryExpression) override;
    std::any visitVariableExpression(const Expression::VariableExpression &variableExpression) override;
    std::any visitAssignmentExpression(const Expression::AssignmentExpression &assignmentExpression) override;
    std::any visitLogicExpression(const Expression::LogicExpression &assignmentExpression) override;

    // statement node visitors
    std::any visitExpressionStatement(const Statement::ExpressionStatement& expressionStatement) override;
    std::any visitPrintStatement(const Statement::PrintStatement &printStatement) override;
    std::any visitVarStatement(const Statement::VarStatement &) override;
    std::any visitBlockStatement(const Statement::BlockStatement &) override;
    std::any visitIfStatement(const Statement::IfStatement&) override;
    std::any visitWhileStatement(const Statement::WhileStatement&) override;
    std::any visitForStatement(const Statement::ForStatement&) override;

    EnvironmentManager environment;
};
