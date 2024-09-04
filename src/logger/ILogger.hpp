#pragma once
#include <functional>
#include <iostream>
#include <string>
#include <functional>

namespace Logging
{
    enum class LOG_LEVEL
    {
        Error,
        Warning,
        Info,
        Disabled,
    };

    /*
     * @brief : pattern matching from functional programming to abstract,encapsulate,DRY switch over LOG_LEVEL(s)
     * NOTE: over-Engineering , not useful I KNOW ,shutup
     */
    struct LogLevelPattenMatcher
    {
        std::function<void()> ErrorCallBack;
        std::function<void()> WarningCallBack;
        std::function<void()> InfoCallBack;
    };

    void patternMatchLogLevel(const LOG_LEVEL &logLevel, const LogLevelPattenMatcher &callBacks);
    std::string stringfyLogLevel(const LOG_LEVEL &logLevel);

    class ILogger
    {
    public:
        ILogger();

        void setLogLevel(const LOG_LEVEL &logLevel);
        virtual void Log(const std::string &message) final;
        virtual void Warn(const std::string &message) final;
        virtual void Error(const std::string &message) final;

        virtual ~ILogger() = default;

    protected:
        virtual void messagePrinter(const std::string &message, const LOG_LEVEL &messageLevel) = 0;

    private:
        LOG_LEVEL logLevel;
    };

}
