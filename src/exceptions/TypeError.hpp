#pragma once

#include "exceptions/LoxError.hpp"
#include "stringBuilder/StringBuilder.hpp"
#include "tokens/Token.hpp"
#include <exception>
#include <string>

class TypeError : public LoxError
{
public:
    TypeError(const Tokens::Token& token,const std::string& message)
    {
        this->token = token;
        this->message = message;
    }
    std::string errorMessage() const override
    {
        return StringBuilder()
                .add(std::string("Type Error"))
                .add(token.lexeme)
                .add(std::string("At line"))
                .add(std::to_string(token.lineNumber))
                .build();
    }

    Tokens::Token token;
private:
    std::string message;
};
