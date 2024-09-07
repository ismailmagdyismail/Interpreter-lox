#pragma once

// system imports
#include <iostream>

// tokens
#include "tokens/Token.hpp"

class Lexer
{
public:
    Lexer(const std::string& sourceCode);
    std::vector<Tokens::Token> scan();
private:
    std::string sourceCode;
};
