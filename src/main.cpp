#include <cstdlib>
#include <iostream>
#include <memory>
#include "logger/FileLogger.hpp"
#include "logger/ILogger.hpp"
#include "logger/ConsoleLogger.hpp"

int main(int argc, char **argv)
{
    system("pwd");
    std::unique_ptr<Logging::ILogger> logger = std::make_unique<FileLogger>(".logs/logs.logs");
    logger->Error("Erorr message testing");
    logger->Warn("Warning message testing");
    logger->Log("Info message testing");
}
