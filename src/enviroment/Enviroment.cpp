#include <memory>
#include <stdexcept>

#include "enviroment/Enviroment.hpp"
#include "exceptions/RunTimeError.hpp"
#include "tokens/Token.hpp"

Environment::Environment(std::shared_ptr<Environment> parentEnviroment)
{
    this->parentEnvironment = parentEnviroment;
}

void Environment::bind(const Tokens::Token &symbol, std::any value)
{
    if(environment.find(symbol.lexeme) != environment.end())
    {
        throw RunTimeError(symbol,"Symbol is already defined");
    }
    environment[symbol.lexeme] = value;
}

void Environment::assign(const Tokens::Token &symbol, std::any value)
{
    if(environment.find(symbol.lexeme) != environment.end())
    {
        environment[symbol.lexeme] = value;
        return;
    }
    if(parentEnvironment == nullptr)
    {
        throw RunTimeError(symbol,"cannot assign, Symbol is not defined");
    }
    parentEnvironment->assign(symbol,value);
}

std::any Environment::read(const Tokens::Token &symbol)
{
    if(environment.find(symbol.lexeme) != environment.end())
    {
        return environment[symbol.lexeme];
    }
    if(parentEnvironment == nullptr)
    {
        throw RunTimeError(symbol,"cannot read, Symbol is not defined");
    }
    return parentEnvironment->read(symbol);
}
