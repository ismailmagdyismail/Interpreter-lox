#pragma once

#include <any>
#include <string>
#include <unordered_map>

#include "tokens/Token.hpp"

class Enviroment
{
public:
    void bind(const Tokens::Token &symbol, std::any value);
    void assign(const Tokens::Token &symbol, std::any value);
    std::any read(const Tokens::Token& symbolName);
private:
    std::unordered_map<std::string, std::any> enviroment;
};
