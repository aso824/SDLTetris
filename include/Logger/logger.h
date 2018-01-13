#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>

#include "loglevel.h"

namespace Logger {
    class Logger
    {
        public:
            static Logger& getInstance();
            ~Logger();

            void log(std::string msg, LogLevel level = TEXT);

            static void error(std::string msg);
            static void warn(std::string msg);
            static void info(std::string msg);
            static void ok(std::string msg);
            static void text(std::string msg);
            static void debug(std::string msg);

        protected:
            Logger();

            void consoleWrite(std::string msg, LogLevel level);
            void setColor(LogLevel level);
            void resetColor();
            void writeTag(LogLevel level, bool colors = true);
    };
}

#endif // LOGGER_H
