#include "sourceReader/ISourceReader.hpp"

class ConsoleReader : public ISourceReader
{
public:
  std::optional<std::string> read() override;
};
