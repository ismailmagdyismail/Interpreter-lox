#pragma once

#include <any>

namespace Statement
{
    class PrintStatement;
    class ExpressionStatement;
}

class IStatementVisitor
{
public:
    virtual std::any visitPrintStatement(const Statement::PrintStatement& printStatement) = 0;
    virtual std::any visitExpressionStatement(const Statement::ExpressionStatement&) = 0;
    virtual ~IStatementVisitor() = default;
};
