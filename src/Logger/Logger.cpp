#include "Logger.hpp"
#include <iostream>
#include <ctime>
#include <vector>

std::vector<LogEntry> Logger::messages;

std::string currentTimeToString()
{
    time_t now = time(0);
    std::string output(30, '\0');
    std::strftime(&output[0], output.size(), "%m/%d/%Y %T", localtime(&now));
    return output;
}

void Logger::Log(const std::string& msg)
{
    LogEntry logEntry;
    logEntry.type = LOG_INFO;
    logEntry.message = "LOG | " + currentTimeToString() + " - " + msg;
    std::cout << "\033[32m" << logEntry.message << std::endl;
    messages.push_back(logEntry);
}

void Logger::Warn(const std::string& msg)
{
    LogEntry logEntry;
    logEntry.type = LOG_WARNING;
    logEntry.message = "WARN | " + currentTimeToString() + " - " + msg;
    std::cout << "\033[33m" << logEntry.message << std::endl;
    messages.push_back(logEntry);
}


void Logger::Err(const std::string& msg)
{
    LogEntry logEntry;
    logEntry.type = LOG_ERROR;
    logEntry.message = "ERR | " + currentTimeToString() + " - " + msg;
    std::cerr << "\033[31m" << logEntry.message << std::endl;
    messages.push_back(logEntry);
}
