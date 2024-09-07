// system imports
#include <vector>


#include "lexer/Lexer.hpp"
#include "tokens/Token.hpp"

Lexer::Lexer(const std::string& sourceCode):sourceCode{sourceCode}
{
}

std::vector<Tokens::Token> Lexer::scan()
{
    return std::vector<Tokens::Token>();
}
