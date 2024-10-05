#pragma once

#include <exception>
#include <string>

class LoxError : public std::exception
{
public:
    virtual std::string errorMessage() const = 0;
    virtual ~LoxError() = default;
};
