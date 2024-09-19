#pragma once

#include "sourceReporter/IReportMessage.hpp"
#include "sourceReporter/LineDescriptor.hpp"
#include <iostream>

namespace SourceReport
{
    class LineError : public IReportMessage
    {
    public:
        LineError(const LineDescriptor &, const std::string &errorMessage);
        std::string formatReport() const override;
        bool isValid() const override;
        bool isOfType(const ReportMessageLevel &messageType) const override;

    private:
        std::string errorMessage;
    };
}
