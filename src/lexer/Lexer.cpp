// system imports
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <memory.h>

#include "lexer/Lexer.hpp"
#include "sourceReporter/IReportMessage.hpp"
#include "sourceReporter/LineError.hpp"
#include "sourceReporter/SourceReporter.hpp"
#include "tokens/Token.hpp"

#define LINE_FEED 10

bool isWhiteSpace(const char& charachtar)
{
    return charachtar == ' ' || charachtar == '\t' || charachtar == '\r';
}

bool isNewLine(const char& charachtar)
{
    return charachtar == '\n' || int(charachtar) == LINE_FEED;
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

std::vector<Tokens::Token> Lexer::scan(SourceReport::SourceReporter& reporter)
{
    std::vector<Tokens::Token> tokens;
    std::string lexeme;
    while (!this->atEnd())
    {
        char charToProcess = this->sourceCode[this->currentIndex];
        if(isNewLine(charToProcess))
        {
            this->lineNumber++;
        }
        if(lexeme.empty() && (isWhiteSpace(charToProcess) || isNewLine(charToProcess)))
        {
            advance();
            continue;
        }
        if(!lexeme.empty() && (
            isWhiteSpace(charToProcess) ||
            Tokens::isSingleCharToken(std::string(1,charToProcess)) ||
            isNewLine(charToProcess)
        ))
        {
            Tokens::Token token = Tokens::createToken(lexeme,this->lineNumber);
            tokens.push_back(token);
            lexeme.clear();
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
                while (!isNewLine(peekNext()) && !atEnd())
                {
                    advance();
                }
                continue;
            }
            Tokens::Token token = Tokens::createToken(lexeme,this->lineNumber);
            tokens.push_back(token);
            lexeme.clear();
        }
        this->advance();
    }
    if(!lexeme.empty())
    {
        tokens.push_back(Tokens::createToken(lexeme,this->lineNumber));
        lexeme.clear();
    }
    return tokens;
}
