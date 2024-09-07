#pragma once

#include "sourceReporter/IReportMessage.hpp"
#include <iostream>

namespace SourceReport
{
    class LineError : public IReportMessage
    {
        public:
            std::string formatReport() const override;
            bool isValid() const override;
            bool isOfType(const ReportMessageType& messageType) const override;

        private:
            std::string errorMessage;
            unsigned int errorPosition;
    };
}
