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

bool isNegligibleChar(const char& charachtar)
{
    return charachtar == ' ' || charachtar == '\n';
}

Lexer::Lexer(const std::string& sourceCode):sourceCode{sourceCode}
{
    this->currentIndex = 0;
    this->lineNumber = 0;
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
        return ' ';
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
        if(lexeme.empty() && isNegligibleChar(charToProcess))
        {
            advance();
            continue;
        }
        std::cout<<"HERE "<<charToProcess<<'\n';
        if(!lexeme.empty() && (charToProcess == ' ' || Tokens::isSingleCharToken(std::string(1,charToProcess))) )
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
