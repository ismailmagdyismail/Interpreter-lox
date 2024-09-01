#include "sourceReader/ISourceReader.hpp"

class FileReader : public ISourceReader
{
public:
  FileReader(std::string &&fileName);
  FileReader(const std::string &fileName);
  std::optional<std::string> read() override;

private:
  std::string fileName;
};