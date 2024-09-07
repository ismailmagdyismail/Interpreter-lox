#include "sourceReporter/LineDescriptor.hpp"

namespace SourceReport
{
    LineDescriptor::LineDescriptor(const std::string& lineContent,const unsigned int& lineNumber)
    :lineContent(lineContent),lineNumber_(lineNumber){}

    unsigned int LineDescriptor::lineSize()
    {
        return this->lineContent.size();
    }

    unsigned int LineDescriptor::lineNumber()
    {
        return this->lineNumber_;
    }

    char LineDescriptor::getCharAt(unsigned int location)
    {
        if(location >= this->lineSize())
        {
            return char();
        }
        return this->lineContent[location];
    }
}
