// system imports
#include <_ctype.h>
#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <memory.h>

#include "lexer/Lexer.hpp"
#include "sourceReporter/IReportMessage.hpp"
#include "sourceReporter/LineDescriptor.hpp"
#include "sourceReporter/LineError.hpp"
#include "sourceReporter/SourceReporter.hpp"
#include "tokens/Token.hpp"

#define DEFAULT_ERROR_POS 0

bool isWhiteSpace(const char& charachtar)
{
    return charachtar == ' ' || charachtar == '\t' || charachtar == '\r';
}

bool isNewLine(const char& charachtar)
{
    return int(charachtar) == 10;
}

Lexer::Lexer(const std::string& sourceCode):sourceCode{sourceCode}
{
    this->currentIndex = 0;
    this->lineNumber = 1;
}

bool Lexer::atEnd() const
{
    return this->currentIndex >= this->sourceCode.size();
}

bool Lexer::hasNext() const
{
    return this->currentIndex + 1 < this->sourceCode.size();
}

char Lexer::peekNext() const
{
    if(!hasNext())
    {
        return '\0';
    }
    return this->sourceCode[this->currentIndex + 1];
}

char Lexer::current() const
{
    if(!atEnd())
    {
        return this->sourceCode[this->currentIndex];
    }
    return  '\0';
}

void Lexer::advance()
{
    if(!atEnd())
    {
        this->currentIndex++;
    }
}


// NOTE: more generic scanner than switching over each token type
//  + easier to add new tokens
//  - harder to understand
//  TODO: might add support for 2 versions [Generic,simple with switch case]

std::vector<Tokens::Token> Lexer::scan(SourceReport::SourceReporter& reporter)
{
    while (!atEnd())
    {
        if(isWhiteSpace(current()))
        {
            advance();
        }
        else if(isNewLine(current()))
        {
            this->lineNumber++;
            advance();
        }
        else if(Tokens::isSingleCharToken(std::string(1,current())))
        {
            // LEAKY ABSTRACTION , how do you know the comment is of length 2 , SO
            // Generalization goes out of the window
            // Could be more generalized more if delegated to tokens , but less performant
            std::string TwoCharLexeme = std::string() + current() + peekNext();
            if(Tokens::isSingleLineComment(TwoCharLexeme))
            {
                scanSingleLineComment();
            }
            else if(Tokens::isMultiLineCommentStart(TwoCharLexeme))
            {
                scanMultiLineComment(reporter);
            }
            // Could be generalized to is StopWord / ValidToken to of arbitrary length
            else if(Tokens::isTwoCharToken(TwoCharLexeme))
            {
                Tokens::Token token = Tokens::createToken(TwoCharLexeme,this->lineNumber);
                tokens.push_back(token);
                // skip two char keyword
                advance();
                advance();
            }
            else
            {
                Tokens::Token token = Tokens::createToken(std::string(1,current()),this->lineNumber);
                tokens.push_back(token);
                // skip two char keyword
                advance();
            }
        }
        else if(current() == '"')
        {
            scanStringLiteral(reporter);
        }
        else if(std::isdigit(current()))
        {
            scanDigit();
        }
        else if(std::isalpha(current()))
        {
            scanIdentifier();
        }
        else
        {
            SourceReport::LineError lineError(SourceReport::LineDescriptor(lineNumber),"Undefined Token");
            reporter.addMessage(std::make_unique<SourceReport::LineError>(lineError));
            advance();
        }
    }
    Tokens::Token eofToken = Tokens::createToken(Tokens::TokenType::END_OF_FILE,"",this->lineNumber);
    tokens.push_back(eofToken);
    return tokens;
}

void Lexer::scanSingleLineComment()
{
    while (!isNewLine(current()) && !atEnd())
    {
        advance();
    }
}

void Lexer::scanMultiLineComment(SourceReport::SourceReporter& reporter)
{
    // skip starting /*
    unsigned int startingLineNumber = this->lineNumber;
    advance();
    advance();
    while (
        !atEnd() &&
        !Tokens::isMultiLineCommentEnd(std::string(1,current()) + peekNext())
    )
    {
        if(current() == '\n')
        {
            this->lineNumber++;
        }
        advance();
    }
    if(atEnd())
    {
        SourceReport::LineError lineError(SourceReport::LineDescriptor(startingLineNumber),"Non Terminating comment");
        reporter.addMessage(std::make_unique<SourceReport::LineError>(lineError));
        return;
    }
    // skip terminating */
    advance();
    advance();
}

void Lexer::scanStringLiteral(SourceReport::SourceReporter& reporter)
{
    // starting "
    advance();
    std::string stringLiteral;
    unsigned startingLineNumber  = this->lineNumber;
    while (current() != '"' && !atEnd())
    {
        if(isNewLine(current()))
        {
            this->lineNumber++;
        }
        stringLiteral += current();
        advance();
    }
    if(current() != '"')
    {
        SourceReport::LineError lineError(SourceReport::LineDescriptor(startingLineNumber),"No Treminating \" was found");
        reporter.addMessage(std::make_unique<SourceReport::LineError>(lineError));
        return;
    }
    // terminating "
    advance();
    this->tokens.push_back(Tokens::createToken(Tokens::TokenType::STRING,stringLiteral,startingLineNumber));
}


void Lexer::scanDigit()
{
    std::function<std::string()> parseDigits = [this]() -> std::string
    {
        std::string digits;
        while (isdigit(current()) && !atEnd())
        {
            digits += current();
            advance();
        }
        return digits;
    };

    std::string number = parseDigits();
    if(current() == '.' && isdigit(peekNext()))
    {
        number += current();
        advance();
        number += parseDigits();
    }
    this->tokens.push_back(Tokens::createToken(Tokens::TokenType::NUMBER,number,this->lineNumber));
}

void Lexer::scanIdentifier()
{
    std::string identifier;
    while (std::isalnum(current()) && !atEnd())
    {
        identifier += current();
        advance();
    }
    this->tokens.push_back(Tokens::createToken(Tokens::TokenType::IDENTFIER,identifier,this->lineNumber));
}
