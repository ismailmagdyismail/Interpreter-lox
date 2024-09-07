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

            virtual std::string formatReport() = 0;
            virtual bool isValid() = 0;
            virtual bool isOfType(const ReportMessageType& messageType) = 0;
            char getCharAt(unsigned int location);
            unsigned int lineSize();
            unsigned int lineNumber();

            virtual ~IReportMessage() = default;
        private:
            LineDescriptor lineDescriptor;
    };
}
