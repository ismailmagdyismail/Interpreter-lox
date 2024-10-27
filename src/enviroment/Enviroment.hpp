#pragma once

#include <any>
#include <memory>
#include <string>
#include <unordered_map>

#include "tokens/Token.hpp"

class Environment
{
public:
    Environment() = default;
    Environment(std::shared_ptr<Environment> parentEnviroment);
    void bind(const Tokens::Token &symbol, std::any value);
    void assign(const Tokens::Token &symbol, std::any value);
    std::any read(const Tokens::Token& symbolName);
private:
    std::shared_ptr<Environment> parentEnvironment;
    std::unordered_map<std::string, std::any> environment;
};
