#include "tokens/Token.hpp"
#include <optional>
#include <unordered_map>
#include <set>

static std::set<std::string> keyWordsTokens = {
    "and",
    "or",
    "class",
    "true",
    "false",
    "fun",
    "for",
    "while",
    "if",
    "else",
    "nil",
    "print",
    "return",
    "super",
    "this",
    "var",
    "eof"
};

static std::set<std::string> singleCharTokens = {
    "(",
    ")",
    "{",
    "}",
    ",",
    ".",
    "-",
    "+",
    ";",
    "/",
    "*",
    "!",
    "=",
    ">",
    "<",
};

static std::set<std::string> twoCharTokens = {
    "!=",
    "==",
    ">=",
    "<=",
};

namespace Tokens
{
    bool isSingleCharToken(const std::string &lexeme)
    {
        return singleCharTokens.find(lexeme) != singleCharTokens.end();
    }

    bool isTwoCharToken(const std::string &lexeme)
    {
        return twoCharTokens.find(lexeme) != twoCharTokens.end();
    }

    bool isKeyword(const std::string &lexeme)
    {
        return keyWordsTokens.find(lexeme) != keyWordsTokens.end();
    }

    bool isReserved(const std::string &lexeme)
    {
        return isSingleCharToken(lexeme) || isTwoCharToken(lexeme) || isKeyword(lexeme);
    }

    std::optional<Token> createToken(const TokenType &tokenType,const std::string& lexeme,const unsigned int& lineNumber)
    {
        if(isReserved(lexeme))
        {
            return Token{
                .tokenType = tokenType,
                .lexeme = lexeme,
                .lineNumber = lineNumber,
            };
        }
        // TODO: check for valid identifiers / nums / strings
        return Token{
            .tokenType = tokenType,
            .lexeme = lexeme,
            .lineNumber = lineNumber,
        };
    }
}
