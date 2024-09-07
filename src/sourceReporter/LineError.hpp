#pragma once

#include "sourceReporter/IReportMessage.hpp"
#include <iostream>

namespace SourceReport
{
    class LineError : public IReportMessage
    {
        public:
            std::string report() override;
            bool isValid() override;
            bool isOfType(const ReportMessageType& messageType) override;

        private:
            std::string errorMessage;
            unsigned int errorPosition;
    };
}
