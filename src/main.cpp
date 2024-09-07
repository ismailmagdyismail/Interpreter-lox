// system imports
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <vector>

// logger
#include "lexer/Lexer.hpp"
#include "logger/ConsoleLogger.hpp"

// source file readers
#include "sourceReader/ISourceReader.hpp"
#include "sourceReader/ConsoleReader.hpp"
#include "sourceReader/FileReader.hpp"
#include "tokens/Token.hpp"

static std::unique_ptr<Logging::ILogger> logger = std::make_unique<ConsoleLogger>();
static std::unique_ptr<ISourceReader> sourceReader;

static void runLexer(const std::string& source);
static void runConsoleREPL();
static void runReadFile(const std::string& fileName);

int main(int argc, char **argv)
{
    logger->Log("number of args passed "+ std::to_string(argc));
    for(int i = 0 ;i<argc;i++)
    {
        logger->Log("Parameter "+std::to_string(i) +" is "+argv[i]);
    }
    if(argc <= 1)
    {
        runConsoleREPL();
    }
    else if(argc == 2)
    {
        runReadFile(argv[1]);
    }
    else
    {
        logger->Error("Invalid number of args , terminating LOX-Interpreter");
    }
}

void runConsoleREPL()
{
    sourceReader = std::move(std::make_unique<ConsoleReader>());
    logger->Log("Reading from console\n");
    while (true)
    {
        std::cout<<"> ";
        std::string input;
        std::getline(std::cin,input);
        logger->Log("Read line from console = " + input);
        if(input == "-1")
        {
            break;
        }
        runLexer(input);
    }
}

void runReadFile(const std::string& fileName)
{
    logger->Log("Reading from Source files\n");
    std::string filePath = fileName;
    if(filePath.find("source_files") == filePath.npos)
    {
        filePath = std::string("source_files/")  + filePath;
    }
    sourceReader = std::move(std::make_unique<FileReader>(filePath));
    std::optional<std::string> sourceCode = sourceReader->read();
    if(!sourceCode.has_value())
    {
        logger->Error("Could source code from this file path" + filePath);
        return;
    }
    logger->Log("File contnent\n"+sourceCode.value());
    runLexer(sourceCode.value());
}


void runLexer(const std::string& source)
{
    // Lexer lexer(source);
    // std::vector<Tokens::Token> tokens = lexer.scan();
}
