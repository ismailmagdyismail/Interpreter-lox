#pragma once

#include "sourceReporter/IReportMessage.hpp"
#include <memory>
#include <vector>

namespace SourceReport
{
    class SourceReporter
    {
    public:
        SourceReporter() = default;
        SourceReporter(const SourceReporter& other) = delete;
        SourceReporter(SourceReporter&& other) = default;

        void addMessage(std::unique_ptr<IReportMessage> &&message);
        bool hasError() const;
        std::vector<std::string> formatReports(const ReportMessageType& messageType) const;

    private:
        std::vector<std::unique_ptr<IReportMessage>> reportMessages;
    };
}
