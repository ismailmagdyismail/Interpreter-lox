// system imports
#include <algorithm>
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

void Lexer::advance()
{
    this->currentIndex++;
}


// NOTE: more generic scanner than switching over each token type
//  + easier to add new tokens
//  - harder to understand
//  TODO: might add support for 2 versions [Generic,simple with switch case]

std::vector<Tokens::Token> Lexer::scan(SourceReport::SourceReporter& reporter)
{
    std::string lexeme;
    while (!atEnd())
    {
        char charToProcess = this->sourceCode[this->currentIndex];
        if(lexeme.empty() && (
            isWhiteSpace(charToProcess) ||
            isNewLine(charToProcess)) ||
            charToProcess == '"'
        )
        {
            this->lineNumber += isNewLine(charToProcess);
            if(charToProcess == '"')
            {
                scanStringLiteral(reporter);
                continue;
            }
            advance();
            continue;
        }
        if(!lexeme.empty() && (
            isWhiteSpace(charToProcess) ||
            Tokens::isSingleCharToken(std::string(1,charToProcess)) ||
            isNewLine(charToProcess) ||
            charToProcess == '"'
        ))
        {
            Tokens::Token token = Tokens::createToken(lexeme,this->lineNumber);
            tokens.push_back(token);
            lexeme.clear();
            if(charToProcess == '"')
            {
                scanStringLiteral(reporter);
            }
            continue;
        }
        lexeme += charToProcess;
        if(Tokens::isSingleCharToken(lexeme))
        {
            if(hasNext() && Tokens::isTwoCharToken(lexeme + peekNext()))
            {
                lexeme += peekNext();
                advance();
            }
            else if(hasNext() && Tokens::isComment(lexeme + peekNext()))
            {
                lexeme.clear();
                while (!isNewLine(charToProcess) && !atEnd())
                {
                    advance();
                    charToProcess = this->sourceCode[this->currentIndex];
                }
                continue;
            }
            Tokens::Token token = Tokens::createToken(lexeme,this->lineNumber);
            tokens.push_back(token);
            lexeme.clear();
        }
        advance();
    }
    if(!lexeme.empty())
    {
        tokens.push_back(Tokens::createToken(lexeme,this->lineNumber));
        lexeme.clear();
    }
    return tokens;
}

void Lexer::scanStringLiteral(SourceReport::SourceReporter& reporter)
{
    advance();
    char charToProcess = this->sourceCode[currentIndex];
    std::string stringLiteral;
    unsigned startingLineNumber  = this->lineNumber;
    while (charToProcess != '"' && !atEnd())
    {
        if(isNewLine(charToProcess))
        {
            this->lineNumber++;
        }
        stringLiteral += charToProcess;
        advance();
        charToProcess = this->sourceCode[currentIndex];
    }
    if(charToProcess != '"')
    {
        SourceReport::LineError lineError(SourceReport::LineDescriptor("No Treminating \" was found",startingLineNumber),"",DEFAULT_ERROR_POS);
        reporter.addMessage(std::make_unique<SourceReport::LineError>(lineError));
        return;
    }
    advance();
    this->tokens.push_back(Tokens::createToken(stringLiteral,this->lineNumber));
}
