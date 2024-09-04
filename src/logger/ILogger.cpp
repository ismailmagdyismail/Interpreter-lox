#include "logger/ILogger.hpp"

Logging::ILogger::ILogger()
{
    this->logLevel = Logging::LOG_LEVEL::Info;
}

void Logging::ILogger::setLogLevel(const LOG_LEVEL &logLevel)
{
    this->logLevel = logLevel;
}

void Logging::ILogger::Log(const std::string &message)
{
    if (this->logLevel != LOG_LEVEL::Info)
    {
        return;
    }
    this->messagePrinter(message, LOG_LEVEL::Info);
}

void Logging::ILogger::Error(const std::string &message)
{
    if (this->logLevel == LOG_LEVEL::Disabled)
    {
        return;
    }
    this->messagePrinter(message, LOG_LEVEL::Error);
}

void Logging::ILogger::Warn(const std::string &message)
{
    if (this->logLevel == LOG_LEVEL::Disabled || this->logLevel == LOG_LEVEL::Error)
    {
        return;
    }
    this->messagePrinter(message, LOG_LEVEL::Warning);
}

void Logging::patternMatchLogLevel(const Logging::LOG_LEVEL &logLevel, const Logging::LogLevelPattenMatcher &callBacks)
{
    if (logLevel == Logging::LOG_LEVEL::Error)
    {
        if (callBacks.ErrorCallBack)
        {
            callBacks.ErrorCallBack();
        }
    }
    else if (logLevel == Logging::LOG_LEVEL::Warning)
    {
        if (callBacks.WarningCallBack)
        {
            callBacks.WarningCallBack();
        }
    }
    else if (logLevel == Logging::LOG_LEVEL::Info)
    {
        if (callBacks.InfoCallBack)
        {
            callBacks.InfoCallBack();
        }
    }
}

std::string Logging::stringfyLogLevel(const LOG_LEVEL &logLevel)
{
    std::string logLevelStr = "";

    LogLevelPattenMatcher matcher{
        .ErrorCallBack = [&logLevelStr]()
        { logLevelStr = "Error"; },
        .WarningCallBack = [&logLevelStr]()
        { logLevelStr = "Warning"; },
        .InfoCallBack = [&logLevelStr]()
        { logLevelStr = "Info"; },
    };
    patternMatchLogLevel(logLevel, matcher);
    return logLevelStr;
}
