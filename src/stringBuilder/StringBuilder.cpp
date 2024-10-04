#include "stringBuilder/StringBuilder.hpp"
#include <utility>

StringBuilder& StringBuilder::add(const std::string &string)
{
    this->str += string;
    this->str += " ";
    return *this;
}


StringBuilder& StringBuilder::add(std::string &&string)
{
    this->str += std::move(string);
    this->str += " ";
    return *this;
}

std::string StringBuilder::build() const
{
    return this->str;
}
