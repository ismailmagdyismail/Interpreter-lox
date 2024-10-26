#pragma once

#include<any>

class IStatementVisitor;

namespace Statement
{
    class IStatement
    {
    public:
        virtual std::any accept(IStatementVisitor& visitor) const = 0;
        virtual ~IStatement() = default;
    };
}
