#include "sourceReporter/SourceReporter.hpp"
#include "sourceReporter/IReportMessage.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

namespace SourceReport
{
    void SourceReporter::addMessage(std::unique_ptr<IReportMessage> &&message)
    {
        this->reportMessages.push_back(std::move(message));
    }

    std::vector<std::string> SourceReporter::formatReports(const ReportMessageType& messageType) const
    {
        std::vector<std::string> reports;
        for (auto &message : this->reportMessages)
        {
            if(message->isOfType(messageType))
            {
                reports.push_back(message->formatReport());
            }
        }
        return reports;
    }

    // TODO: cache this in class , instead of lazily computing it each time we want to check for errors
    bool SourceReporter::hasError() const
    {
        for (auto &message : this->reportMessages)
        {
            if (!message->isValid())
            {
                return false;
            }
        }
        return true;
    }
}
