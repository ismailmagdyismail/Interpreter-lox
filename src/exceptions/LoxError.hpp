#pragma once

#include "tokens/Token.hpp"
#include <exception>
#include <string>

class LoxError : public std::exception
{
public:
    LoxError(const Tokens::Token& token,const std::string& message):token{token},message{message}{};
    Tokens::Token token;
    virtual std::string errorMessage() const = 0;
    virtual ~LoxError() = default;
protected:
    std::string message;
};
