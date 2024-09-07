#include "sourceReporter/LineDescriptor.hpp"

namespace SourceReport
{
    LineDescriptor::LineDescriptor(const std::string &lineContent, const unsigned int &lineNumber)
        : lineContent(lineContent), lineNumber_(lineNumber) {}

    unsigned int LineDescriptor::lineSize() const
    {
        return this->lineContent.size();
    }

    unsigned int LineDescriptor::lineNumber() const
    {
        return this->lineNumber_;
    }

    char LineDescriptor::getCharAt(unsigned int location) const
    {
        if (location >= this->lineSize())
        {
            return char();
        }
        return this->lineContent[location];
    }
}
