#include "enviroment/EnviromentManager.hpp"
#include "exceptions/RunTimeError.hpp"

EnvironmentManager::EnvironmentManager():environments{Environment{}}{}

void EnvironmentManager::pushScope()
{
    environments.push_back(Environment{});
}

void EnvironmentManager::popScope()
{
    if(environments.size() > 1)
    {
        environments.pop_back();
    }
}

void EnvironmentManager::bind(const Tokens::Token &symbol, std::any value)
{
    processNestedEnviroments(
        [&](Environment& enviroment)-> bool { return enviroment.bind(symbol,value); },
        symbol,
        "Symbol is already defined"
    );
}

void EnvironmentManager::assign(const Tokens::Token &symbol, std::any value)
{
    processNestedEnviroments(
        [&](Environment& enviroment)-> bool { return enviroment.assign(symbol,value); },
        symbol,
        "cannot assign, Symbol is not defined"
    );
}

std::any EnvironmentManager::read(const Tokens::Token &symbol)
{
    std::any readSymbol;
    processNestedEnviroments(
        [&](Environment& enviroment)-> bool {
            std::optional<std::any> readEntry =  enviroment.read(symbol);
            if(readEntry.has_value())
            {
                readSymbol = readEntry.value();
                return true;
            }
            return false;
        },
        symbol,
        "cannot read, Symbol is not defined"
    );
    return readSymbol;
}

void EnvironmentManager::processNestedEnviroments(std::function<bool(Environment& env)>taskHandler,const Tokens::Token &symbol,const std::string& errorMessage)
{
    for(int i = environments.size() - 1; i >= 0 ;i--)
    {
        if(taskHandler(environments[i]))
        {
            return;
        }
    }
    throw RunTimeError(symbol,errorMessage);
}
