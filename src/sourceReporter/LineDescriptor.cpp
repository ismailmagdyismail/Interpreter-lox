#include "sourceReporter/LineDescriptor.hpp"

namespace SourceReport
{
    LineDescriptor::LineDescriptor(const unsigned int &lineNumber)
        :lineNumber_(lineNumber) {}

    unsigned int LineDescriptor::lineNumber() const
    {
        return this->lineNumber_;
    }
}
