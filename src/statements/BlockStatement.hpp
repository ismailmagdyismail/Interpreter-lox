#pragma once

#include "statements/IStatement.hpp"
#include <memory>
#include <vector>

namespace Statement
{
    class BlockStatement : public IStatement
    {
    public:
        BlockStatement(std::vector<std::unique_ptr<IStatement>>&& statements);
        std::any accept(IStatementVisitor &visitor) const override;

        std::vector<std::unique_ptr<IStatement>> statements;
    };
}
