#pragma once

#include "sourceReporter/IReportMessage.hpp"
#include "sourceReporter/LineDescriptor.hpp"
#include <iostream>

namespace SourceReport
{
    class LineError : public IReportMessage
    {
    public:
        LineError(const LineDescriptor &, const std::string &errorMessage, const unsigned int &errorPosition);
        std::string formatReport() const override;
        bool isValid() const override;
        bool isOfType(const ReportMessageType &messageType) const override;

    private:
        std::string errorMessage;
        unsigned int errorPosition;
    };
}
