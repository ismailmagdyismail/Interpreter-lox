#pragma once

#include "sourceReporter/LineDescriptor.hpp"
namespace SourceReport
{
    enum class ReportMessageType
    {
        Error,
    };
    class IReportMessage
    {
        public:
            IReportMessage(const LineDescriptor& lineDesc);

            virtual std::string formatReport() const = 0;
            virtual bool isValid() const = 0;
            virtual bool isOfType(const ReportMessageType& messageType) const = 0;
            char getCharAt(unsigned int location) const;
            unsigned int lineSize() const;
            unsigned int lineNumber() const;

            virtual ~IReportMessage() = default;
        private:
            LineDescriptor lineDescriptor;
    };
}
