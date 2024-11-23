#include <memory>
#include <stdexcept>

#include "enviroment/Enviroment.hpp"
#include "exceptions/RunTimeError.hpp"
#include "tokens/Token.hpp"

bool Environment::bind(const Tokens::Token &symbol, std::any value)
{
    if(environment.find(symbol.lexeme) != environment.end())
    {
        return false;
        // throw RunTimeError(symbol,"Symbol is already defined");
    }
    environment[symbol.lexeme] = value;
    return true;
}

bool Environment::assign(const Tokens::Token &symbol, std::any value)
{
    if(environment.find(symbol.lexeme) != environment.end())
    {
        environment[symbol.lexeme] = value;
        return true;
    }
    return false;
    // if(parentEnvironment == nullptr)
    // {
        // throw RunTimeError(symbol,"cannot assign, Symbol is not defined");
    // }
}

std::optional<std::any> Environment::read(const Tokens::Token &symbol)
{
    if(environment.find(symbol.lexeme) != environment.end())
    {
        return environment[symbol.lexeme];
    }
    return {};
    // if(parentEnvironment == nullptr)
    // {
    //     throw RunTimeError(symbol,"cannot read, Symbol is not defined");
    // }
}
