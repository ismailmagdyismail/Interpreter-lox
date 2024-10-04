#pragma once

#include <string>

class StringBuilder
{
public:
    StringBuilder& add(const std::string& string);
    StringBuilder& add(std::string&& string);
    std::string build() const;
private:
    std::string str;
};
