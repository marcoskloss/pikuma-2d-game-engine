#pragma once

#include <string>
#include <vector>

enum LogType  {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
};

struct LogEntry {
        LogType type;
        std::string message;
};

class Logger {
    public:
        static std::vector<LogEntry> messages;
        static void Log(const std::string& msg);
        static void Warn(const std::string& msg);
        static void Err(const std::string& msg);
};

