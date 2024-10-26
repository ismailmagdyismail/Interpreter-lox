#pragma once

#include <any>

namespace Statement
{
    class PrintStatement;
    class ExpressionStatement;
    class VarStatement;
}

class IStatementVisitor
{
public:
    virtual std::any visitPrintStatement(const Statement::PrintStatement& printStatement) = 0;
    virtual std::any visitExpressionStatement(const Statement::ExpressionStatement&) = 0;
    virtual std::any visitVarStatement(const Statement::VarStatement&) = 0;

    virtual ~IStatementVisitor() = default;
};
