#pragma once

#include <any>
#include <memory>
#include <string>
#include <unordered_map>
#include <optional>

#include "tokens/Token.hpp"

class Environment
{
public:
    Environment() = default;
    bool bind(const Tokens::Token &symbol, std::any value);
    bool assign(const Tokens::Token &symbol, std::any value);
    std::optional<std::any> read(const Tokens::Token& symbolName);
private:
    std::unordered_map<std::string, std::any> environment;
};
