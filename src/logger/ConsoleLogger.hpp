#pragma once

#include "logger/ILogger.hpp"

class ConsoleLogger final : public Logging::ILogger
{
protected:
    void messagePrinter(const std::string &message, const Logging::LOG_LEVEL &messageLevel) override;
};
