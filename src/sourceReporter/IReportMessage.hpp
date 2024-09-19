#pragma once

#include "sourceReporter/LineDescriptor.hpp"

namespace SourceReport
{
    enum class ReportMessageLevel
    {
        Error,
    };
    class IReportMessage
    {
    public:
        IReportMessage(const LineDescriptor &lineDesc);

        virtual std::string formatReport() const = 0;
        virtual bool isValid() const = 0;
        virtual bool isOfType(const ReportMessageLevel &messageType) const = 0;
        unsigned int lineNumber() const;

        virtual ~IReportMessage() = default;

    private:
        LineDescriptor lineDescriptor;
    };
}
