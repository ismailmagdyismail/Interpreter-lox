#include "logger/ConsoleLogger.hpp"
#include "logger/ILogger.hpp"
#include <iostream>

void ConsoleLogger::messagePrinter(const std::string &message) const
{
    std::cout << message << '\n';
}
