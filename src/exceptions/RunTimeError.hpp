#pragma once

#include "exceptions/LoxError.hpp"
#include "stringBuilder/StringBuilder.hpp"

class RunTimeError : public LoxError
{
public:
    RunTimeError(const Tokens::Token& token,const std::string& message):LoxError(token,message){};
    std::string errorMessage() const override
    {
        return StringBuilder()
            .add(std::string("RunTime-Error"))
            .add(token.lexeme)
            .add(std::string("At line"))
            .add(std::to_string(token.lineNumber))
            .add(message)
            .build();
    }
};
