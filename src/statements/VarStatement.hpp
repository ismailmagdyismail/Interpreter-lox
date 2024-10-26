#pragma once

#include <memory>

#include "expressions/IExpression.hpp"
#include "statements/IStatement.hpp"
#include "tokens/Token.hpp"

namespace Statement
{
    class VarStatement : public IStatement
    {
    public:
        VarStatement(const Tokens::Token& token,std::unique_ptr<Expression::IExpression>&& value);
        std::any accept(IStatementVisitor &visitor) const override;

        Tokens::Token identifier;
        std::unique_ptr<Expression::IExpression> value ;
    };

}
