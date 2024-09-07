#include "sourceReporter/IReportMessage.hpp"
#include "sourceReporter/LineDescriptor.hpp"

namespace SourceReport
{
    IReportMessage::IReportMessage(const LineDescriptor &lineDesc) : lineDescriptor(lineDesc) {}

    unsigned int IReportMessage::lineSize() const
    {
        return this->lineDescriptor.lineSize();
    }

    unsigned int IReportMessage::lineNumber() const
    {
        return this->lineDescriptor.lineNumber();
    }

    char IReportMessage::getCharAt(unsigned int location) const
    {
        return this->lineDescriptor.getCharAt(location);
    }
}
