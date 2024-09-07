#pragma once

#include <iostream>

namespace SourceReport
{
    class LineDescriptor
    {
        public:
            LineDescriptor(const std::string& line,const unsigned int& linNumber);
            char getCharAt(unsigned int location);
            unsigned int lineSize();
            unsigned int lineNumber();
        private:
            std::string lineContent;
            unsigned int lineNumber_;
    };
}
