#include "sourceReporter/IReportMessage.hpp"
#include "sourceReporter/LineDescriptor.hpp"

namespace SourceReport
{
    IReportMessage::IReportMessage(const LineDescriptor &lineDesc) : lineDescriptor(lineDesc) {}

    unsigned int IReportMessage::lineNumber() const
    {
        return this->lineDescriptor.lineNumber();
    }

}
