#pragma once

#include <iostream>

namespace SourceReport
{
    class LineDescriptor
    {
    public:
        LineDescriptor(const std::string &line, const unsigned int &lineNumber);
        char getCharAt(unsigned int location) const;
        unsigned int lineSize() const;
        unsigned int lineNumber() const;

    private:
        std::string lineContent;
        unsigned int lineNumber_;
    };
}
