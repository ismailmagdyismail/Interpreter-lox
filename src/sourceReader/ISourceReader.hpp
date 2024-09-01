#pragma once

#include <iostream>
#include <optional>

class ISourceReader
{
public:
    virtual std::optional<std::string> read() = 0;
    virtual ~ISourceReader() = default;
};
