/*
 * author: Dylan Campbell
 * contact: campbell.dyl@gmail.com
 * project: 2d game engine
 *
 * This program contains source code from Gustavo Pezzi's "C++ 2D Game Engine
 * Development" course, found here: https://pikuma.com/courses
*/

// -----------------------------------------------------------------------------
// logger.h
// header file for logger class
// -----------------------------------------------------------------------------
#ifndef LOGGER_H
#define LOGGER_H

#include <vector>
#include <string>

enum LogType {
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
        static void Log(const std::string& message);
        static void Err(const std::string& message);
};

#endif
