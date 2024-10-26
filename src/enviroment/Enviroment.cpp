#include <stdexcept>

#include "enviroment/Enviroment.hpp"
#include "exceptions/RunTimeError.hpp"
#include "tokens/Token.hpp"

void Enviroment::bind(const Tokens::Token &symbol, std::any value)
{
    if(enviroment.find(symbol.lexeme) != enviroment.end())
    {
        throw RunTimeError(symbol,"Symbol is already defined");
    }
    enviroment[symbol.lexeme] = value;
}

void Enviroment::assign(const Tokens::Token &symbol, std::any value)
{
    if(enviroment.find(symbol.lexeme) == enviroment.end())
    {
        throw RunTimeError(symbol,"Symbol is not defined");
    }
    enviroment[symbol.lexeme] = value;
}

std::any Enviroment::read(const Tokens::Token &symbol)
{
    if(enviroment.find(symbol.lexeme) == enviroment.end())
    {
        throw RunTimeError(symbol,"Symbol is not defined");
    }
    return enviroment[symbol.lexeme];
}
