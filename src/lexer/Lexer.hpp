#pragma once

// system imports
#include <iostream>

// tokens
#include "sourceReporter/SourceReporter.hpp"
#include "tokens/Token.hpp"

class Lexer
{
public:
    Lexer(const std::string& sourceCode);
    std::vector<Tokens::Token> scan(SourceReport::SourceReporter& reporter);
private:
    bool atEnd() const;
    bool hasNext() const ;
    char peekNext() const;
    void advance();
    std::string sourceCode;
    unsigned int currentIndex;
    unsigned int lineNumber;
};
