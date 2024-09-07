#pragma once

#include <iostream>
#include <optional>

namespace Tokens
{
    enum class TokenType
    {

    };
    struct Token
    {
        TokenType tokenType;
    };

    std::string tokenLiteral(const Token& token);
    std::optional<Token> createToken(const TokenType& tokenType);
}
