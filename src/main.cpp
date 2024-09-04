#include <iostream>
#include <memory>
#include "logger/ILogger.hpp"
#include "logger/ConsoleLogger.hpp"

int main(int argc, char **argv)
{
  std::unique_ptr<Logging::ILogger> logger = std::make_unique<ConsoleLogger>();
  logger->Error("Erorr message testing");
  logger->Warn("Warning message testing");
  logger->Log("Info message testing");
}
