#include "sourceReporter/LineError.hpp"
#include "sourceReporter/IReportMessage.hpp"
#include <string>


namespace SourceReport
{
    std::string LineError::formatReport() const
    {
        return
        std::to_string(this->lineNumber())  + "|" + std::string("[Error]:") +
        this->errorMessage + ", at position " + std::to_string(this->errorPosition) ;
    }

    bool LineError::isOfType(const ReportMessageType& messageType) const
    {
        return messageType == ReportMessageType::Error;
    }

    bool LineError::isValid() const
    {
        return false;
    }
}
