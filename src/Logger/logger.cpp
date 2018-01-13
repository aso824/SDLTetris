#include "include/Logger/logger.h"

Logger::Logger&Logger::Logger::getInstance()
{
    static Logger instance;
    return instance;
}

Logger::Logger::~Logger()
{

}

void Logger::Logger::log(std::string msg, LogLevel level)
{
    this->consoleWrite(msg, level);
}

void Logger::Logger::error(std::string msg)
{
    Logger::getInstance().consoleWrite(msg, LogLevel::ERROR);
}

void Logger::Logger::warn(std::string msg)
{
    Logger::getInstance().consoleWrite(msg, LogLevel::WARN);
}

void Logger::Logger::info(std::string msg)
{
    Logger::getInstance().consoleWrite(msg, LogLevel::INFO);
}

void Logger::Logger::ok(std::string msg)
{
    Logger::getInstance().consoleWrite(msg, LogLevel::OK);
}

void Logger::Logger::text(std::string msg)
{
    Logger::getInstance().consoleWrite(msg, LogLevel::TEXT);
}

void Logger::Logger::debug(std::string msg)
{
    Logger::getInstance().consoleWrite(msg, LogLevel::DEBUG);
}

Logger::Logger::Logger()
{

}

void Logger::Logger::consoleWrite(std::string msg, LogLevel level)
{
    this->writeTag(level, true);
    std::cout << msg << std::endl;
}

void Logger::Logger::setColor(LogLevel level)
{
    #ifdef __linux__

    // Bold text
    std::cout << "\033[1m";

    // Color set
    std::cout << "\033[";

    switch (level) {
        case ERROR: std::cout << "31"; break;
        case WARN: std::cout << "33"; break;
        case INFO: std::cout << "34"; break;
        case OK: std::cout << "32"; break;
        case TEXT: std::cout << "37"; break;
        case DEBUG: std::cout << "35"; break;
        default: std::cout << "37"; break;
    }

    std::cout << "m";

    #endif
}

void Logger::Logger::resetColor()
{
    std::cout << "\033[0m";
}

void Logger::Logger::writeTag(LogLevel level, bool colors)
{
    if (level != TEXT)
        std::cout << "[";

    if (colors)
        this->setColor(level);

    switch (level) {
        case ERROR: std::cout << "err!"; break;
        case WARN: std::cout << "warn"; break;
        case INFO: std::cout << "info"; break;
        case OK: std::cout << " ok "; break;
        case TEXT: std::cout << "       "; break;
        case DEBUG: std::cout << "debug"; break;
        default: std::cout << "       "; break;
    }

    if (colors)
        this->resetColor();

    if (level != TEXT)
        std::cout << "] ";
}
