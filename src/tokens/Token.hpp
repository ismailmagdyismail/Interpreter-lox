#pragma once

#include <iostream>
#include <optional>

namespace Tokens
{
    enum class TokenType
    {
        // Single-character tokens.
        lEFT_PARNTHESES,  // (
        RIGHT_PARNTHESES, // )
        LEFT_BRACE,  // {
        RIGHT_BRACE, // }
        COMMA , // ,
        DOT , // .
        MINUS , // -
        PLUS , // +
        SEMI_COLON , // ;
        SLASH , // /
        STAR , // *
        BANG , // !
        ASSIGN, // =
        GREATER , // >
        SMALLER , // <


        // two character tokens.
        BANG_EQUAL , // !=
        EQUAL , // ==
        GREATER_OR_EQUAL , // >=
        SMALLER_OR_EQUAL , // <=

        // literals
        IDENTFIER,
        STRING,
        NUMBER,

        // keywords
        AND,
        OR,
        CLASS,
        TRUE,
        FALSE,
        FUN,
        FOR,
        WHILE,
        IF,
        ELSE,
        NIL,
        PRINT,
        RETURN,
        SUPER,
        THIS,
        VAR,
        END_OF_FILE,
    };
    struct Token
    {
        TokenType tokenType;
        unsigned int lineNumber;
        std::string lexeme;
    };

    // TODO: consider adding this as a generalization for is single , two char tokens to be able to easily add new tokens , be extenssible
    // bool isStopWord(const std::string& lexeme);
    bool isSingleCharToken(const std::string& lexeme);
    bool isTwoCharToken(const std::string& lexeme);
    bool isKeyword(const std::string& lexeme);
    bool isReserved(const std::string& lexeme);
    std::optional<Token> createToken(const TokenType& tokenType,std::string lexeme);
}
