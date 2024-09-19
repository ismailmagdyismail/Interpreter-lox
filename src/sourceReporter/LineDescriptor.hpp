#pragma once

#include <iostream>

namespace SourceReport
{
    class LineDescriptor
    {
    public:
        LineDescriptor(const unsigned int &lineNumber);
        unsigned int lineNumber() const;

    private:
        unsigned int lineNumber_;
    };
}
