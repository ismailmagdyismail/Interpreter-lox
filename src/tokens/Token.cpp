#include "tokens/Token.hpp"
#include <iostream>
#include <optional>
#include <unordered_map>
#include <set>

static std::unordered_map<std::string, Tokens::TokenType> keyWordsTokens = {
    {"and",Tokens::TokenType::AND},
    {"or",Tokens::TokenType::OR},
    {"class",Tokens::TokenType::CLASS},
    {"true",Tokens::TokenType::TRUE},
    {"false",Tokens::TokenType::FALSE},
    {"fun",Tokens::TokenType::FUNCTION},
    {"for",Tokens::TokenType::FOR},
    {"while",Tokens::TokenType::WHILE},
    {"if",Tokens::TokenType::IF},
    {"else",Tokens::TokenType::ELSE},
    {"nil",Tokens::TokenType::NIL},
    {"print",Tokens::TokenType::PRINT},
    {"return",Tokens::TokenType::RETURN},
    {"super",Tokens::TokenType::SUPER},
    {"this",Tokens::TokenType::THIS},
    {"var",Tokens::TokenType::VAR},
    {"eof",Tokens::TokenType::END_OF_FILE},
};

static std::unordered_map<std::string, Tokens::TokenType> singleCharTokens = {
    {"(",Tokens::TokenType::LEFT_PARNTHESES},
    {")",Tokens::TokenType::RIGHT_PARNTHESES},
    {"{",Tokens::TokenType::LEFT_BRACE},
    {"{",Tokens::TokenType::RIGHT_BRACE},
    {",",Tokens::TokenType::COMMA},
    {".",Tokens::TokenType::DOT},
    {"-",Tokens::TokenType::MINUS},
    {"+",Tokens::TokenType::PLUS},
    {";",Tokens::TokenType::SEMI_COLON},
    {"/",Tokens::TokenType::SLASH},
    {"*",Tokens::TokenType::STAR},
    {"!",Tokens::TokenType::BANG},
    {"=",Tokens::TokenType::ASSIGN},
    {">",Tokens::TokenType::GREATER},
    {"<",Tokens::TokenType::SMALLER},
    {":",Tokens::TokenType::COLON},
    {"?",Tokens::TokenType::QUESTION_MARK},
};

static std::unordered_map<std::string, Tokens::TokenType> twoCharTokens = {
    {"!=",Tokens::TokenType::BANG_EQUAL},
    {"==",Tokens::TokenType::EQUAL},
    {">=",Tokens::TokenType::GREATER_OR_EQUAL},
    {"<=",Tokens::TokenType::SMALLER_OR_EQUAL},
};

namespace Tokens
{
    bool isMatching(const std::string &lexeme, TokenType tokenType)
    {
        return (
            twoCharTokens.find(lexeme) != twoCharTokens.end() && twoCharTokens[lexeme] == tokenType ||
            singleCharTokens.find(lexeme) != singleCharTokens.end() && singleCharTokens[lexeme] == tokenType ||
            keyWordsTokens.find(lexeme) != keyWordsTokens.end() && keyWordsTokens[lexeme] == tokenType
        );
    }
    bool isSingleCharToken(const std::string &lexeme)
    {
        return singleCharTokens.find(lexeme) != singleCharTokens.end();
    }

    bool isTwoCharToken(const std::string &lexeme)
    {
        return twoCharTokens.find(lexeme) != twoCharTokens.end();
    }

    bool isSingleLineComment(const std::string &lexeme)
    {
        return lexeme == "//";
    }

    bool isMultiLineCommentStart(const std::string& lexeme)
    {
        return lexeme == "/*";
    }

    bool isMultiLineCommentEnd(const std::string& lexeme)
    {
        return lexeme == "*/";
    }

    bool isKeyword(const std::string &lexeme)
    {
        return keyWordsTokens.find(lexeme) != keyWordsTokens.end();
    }

    bool isReserved(const std::string &lexeme)
    {
        return isSingleCharToken(lexeme) || isTwoCharToken(lexeme) || isKeyword(lexeme);
    }

    Token createToken(const TokenType &tokenType,const std::string& lexeme,const unsigned int& lineNumber)
    {
        // TODO: should add checks to avoid creating a reserved token with a lexeme that doesn't match it
        // This problem would happend if two diff classes of tokens exist
        return Token{
            .tokenType = tokenType,
            .lexeme = lexeme,
            .lineNumber = lineNumber,
        };
    }

    Token createToken(const std::string& lexeme,const unsigned int& lineNumber)
    {

        if(isSingleCharToken(lexeme))
        {
            return Token{
                .tokenType = singleCharTokens[lexeme],
                .lexeme = lexeme,
                .lineNumber = lineNumber,
            };
        }
        if(isTwoCharToken(lexeme))
        {
            return Token{
                .tokenType = twoCharTokens[lexeme],
                .lexeme = lexeme,
                .lineNumber = lineNumber,
            };
        }
        if(isKeyword(lexeme))
        {
            return Token{
                .tokenType = keyWordsTokens[lexeme],
                .lexeme = lexeme,
                .lineNumber = lineNumber,
            };
        }
        return {
            .tokenType = TokenType::IDENTFIER,
            .lexeme = lexeme,
            .lineNumber = lineNumber,
        };
    }
}
