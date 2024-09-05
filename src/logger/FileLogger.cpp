#include "logger/FileLogger.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>

FileLogger::FileLogger(const std::string& fileName)
{
    this->fileName = fileName;
}

FileLogger::FileLogger(std::string&& fileName)
{
    this->fileName = std::move(fileName);
}

void FileLogger::messagePrinter(const std::string &message) const
{
    std::ofstream file(this->fileName,std::ios::app | std::ios::out);
    if(!file.is_open())
    {
        std::cerr<<"Fatal : file couldn't be opened\n";
        return;
    }
    file << message <<'\n';
}
