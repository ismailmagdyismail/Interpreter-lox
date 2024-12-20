#pragma once

#include "ILogger.hpp"

class FileLogger final : public Logging::ILogger
{
public :
    FileLogger(const std::string& message);
    FileLogger(std::string&& message);

    void messagePrinter(const std::string &message) const override;
private:
    std::string fileName;
};
