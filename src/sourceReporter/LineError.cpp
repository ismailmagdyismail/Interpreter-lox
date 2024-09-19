#include "sourceReporter/LineError.hpp"
#include "sourceReporter/IReportMessage.hpp"
#include "sourceReporter/LineDescriptor.hpp"
#include <string>

namespace SourceReport
{
    LineError::LineError(const LineDescriptor &lineDescriptor, const std::string &errorMessage)
        : IReportMessage(lineDescriptor), errorMessage(errorMessage)
    {}

    std::string LineError::formatReport() const
    {
        return std::to_string(this->lineNumber()) + "|" + std::string("[Error]:") + this->errorMessage ;
    }

    bool LineError::isOfType(const ReportMessageLevel &messageType) const
    {
        return messageType == ReportMessageLevel::Error;
    }

    bool LineError::isValid() const
    {
        return false;
    }
}
