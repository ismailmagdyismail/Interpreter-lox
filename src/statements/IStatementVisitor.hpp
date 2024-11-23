#pragma once

#include <any>

namespace Statement
{
    class PrintStatement;
    class ExpressionStatement;
    class VarStatement;
    class BlockStatement;
    class IfStatement;
    class WhileStatement;
}

class IStatementVisitor
{
public:
    virtual std::any visitPrintStatement(const Statement::PrintStatement& printStatement) = 0;
    virtual std::any visitExpressionStatement(const Statement::ExpressionStatement&) = 0;
    virtual std::any visitVarStatement(const Statement::VarStatement&) = 0;
    virtual std::any visitBlockStatement(const Statement::BlockStatement&) = 0;
    virtual std::any visitIfStatement(const Statement::IfStatement&) = 0;
    virtual std::any visitWhileStatement(const Statement::WhileStatement&) = 0 ;

    virtual ~IStatementVisitor() = default;
};
