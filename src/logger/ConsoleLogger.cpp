#include "logger/ConsoleLogger.hpp"
#include "logger/ILogger.hpp"
#include <iostream>

void ConsoleLogger::messagePrinter(const std::string &message, const Logging::LOG_LEVEL &messageLevel)
{
    std::cout << "[" << Logging::stringfyLogLevel(messageLevel) << "]:" << message << '\n';
}
