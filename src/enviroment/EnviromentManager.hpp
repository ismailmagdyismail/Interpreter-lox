#pragma once

#include <vector>
#include <functional>

#include "enviroment/Enviroment.hpp"

class EnvironmentManager
{
public:
    EnvironmentManager();
    void pushScope();
    void popScope();
    void bind(const Tokens::Token &symbol, std::any value);
    void assign(const Tokens::Token &symbol, std::any value);
    std::any read(const Tokens::Token& symbolName);
private:
    void processNestedEnviroments(std::function<bool(Environment& env)>taskHandler,const Tokens::Token &symbol,const std::string& errorMessage);
    std::vector<Environment>environments;
};
