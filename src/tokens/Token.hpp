#pragma once

#include <iostream>
#include <optional>

namespace Tokens
{
    enum class TokenType
    {
        // Single-character tokens.
        LEFT_PARNTHESES,  // (
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
        QUESTION_MARK ,
        COLON ,


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
        FUNCTION,
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
    bool isStopWord(const std::string& lexeme);
    bool isSingleCharToken(const std::string& lexeme);
    bool isTwoCharToken(const std::string& lexeme);
    bool isSingleLineComment(const std::string& lexeme);
    bool isMultiLineCommentStart(const std::string& lexeme);
    bool isMultiLineCommentEnd(const std::string& lexeme);
    bool isKeyword(const std::string& lexeme);
    bool isReserved(const std::string& lexeme);
    bool isMatching(const std::string& lexeme,TokenType tokenType);
    Token createToken(const TokenType &tokenType,const std::string& lexeme,const unsigned int& lineNumber);
    Token createToken(const std::string& lexeme,const unsigned int& lineNumber);
}
