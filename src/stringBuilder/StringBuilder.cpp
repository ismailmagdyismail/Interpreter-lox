#include "stringBuilder/StringBuilder.hpp"
#include <utility>

StringBuilder& StringBuilder::add(const std::string &string)
{
    this->str += string;
    return *this;
}


StringBuilder& StringBuilder::add(std::string &&string)
{
    this->str += std::move(string);
    return *this;
}

std::string StringBuilder::build() const
{
    return this->str;
}
