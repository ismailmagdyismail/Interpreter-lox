#include "logger/ILogger.hpp"

std::string formatMessage(const std::string& message,const Logging::LOG_LEVEL& logLevel)
{
    return "[" + Logging::stringfyLogLevel(logLevel) + "]" + " : " + message;
}

Logging::ILogger::ILogger()
{
    this->logLevel = Logging::LOG_LEVEL::Info;
    this->enable();
}

void Logging::ILogger::setLogLevel(const LOG_LEVEL &logLevel)
{
    this->enable();
    this->logLevel = logLevel;
}

void Logging::ILogger::disable()
{
    this->disabled = true;
}

void Logging::ILogger::enable()
{
    this->disabled = false;
}

void Logging::ILogger::Log(const std::string &message) const
{
    if (this->logLevel != LOG_LEVEL::Info || this->disabled)
    {
        return;
    }
    this->messagePrinter(formatMessage(message, LOG_LEVEL::Info));
}

void Logging::ILogger::Error(const std::string &message) const
{
    if(this->disabled)
    {
        return;
    }
    this->messagePrinter(formatMessage(message,LOG_LEVEL::Error));
}

void Logging::ILogger::Warn(const std::string &message) const
{
    if (this->logLevel == LOG_LEVEL::Error || this->disabled)
    {
        return;
    }
    this->messagePrinter(formatMessage(message,LOG_LEVEL::Warning));
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
        .ErrorCallBack = [&logLevelStr]() -> void
        { logLevelStr = "Error"; },
        .WarningCallBack = [&logLevelStr]() -> void
        { logLevelStr = "Warn"; },
        .InfoCallBack = [&logLevelStr]() -> void
        { logLevelStr = "Info"; },
    };
    patternMatchLogLevel(logLevel, matcher);
    return logLevelStr;
}
