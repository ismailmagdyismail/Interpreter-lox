#include <fstream>
#include <sstream>

#include "sourceReader/FileReader.hpp"

FileReader::FileReader(const std::string &fileName)
{
  this->fileName = fileName;
}

FileReader::FileReader(std::string &&fileName) : fileName(std::move(fileName))
{
}

std::optional<std::string> FileReader::read()
{
  std::fstream file(this->fileName);
  if (!file)
  {
    return {};
  }
  std::stringstream inputBuffer;
  inputBuffer << file.rdbuf();

  return inputBuffer.str();
}