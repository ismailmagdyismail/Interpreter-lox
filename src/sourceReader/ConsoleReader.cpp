#include "sourceReader/ConsoleReader.hpp"

std::optional<std::string> ConsoleReader::read()
{
  std::string sourceInput;
  std::cin >> sourceInput;
  return sourceInput;
}
