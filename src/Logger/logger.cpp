#include "include/Logger/logger.h"

/**
 * @brief Main method for singleton
 * @return Static Logger instance
 */
Logger::Logger&Logger::Logger::getInstance()
{
    static Logger instance;
    return instance;
}

/**
 * @brief Dtor
 */
Logger::Logger::~Logger()
{

}

/**
 * @brief Main function to log message
 * @param msg Message to be logged (without line breaks)
 * @param level Log level from loglevel.h enum
 */
void Logger::Logger::log(std::string msg, LogLevel level)
{
    this->consoleWrite(msg, level);
}

/**
 * @brief Alias for logging errors
 * @param msg Message to be logged (without line breaks)
 */
void Logger::Logger::error(std::string msg)
{
    Logger::getInstance().consoleWrite(msg, LogLevel::ERROR);
}

/**
 * @brief Alias for logging warnings
 * @param msg Message to be logged (without line breaks)
 */
void Logger::Logger::warn(std::string msg)
{
    Logger::getInstance().consoleWrite(msg, LogLevel::WARN);
}

/**
 * @brief Alias for logging informations
 * @param msg Message to be logged (without line breaks)
 */
void Logger::Logger::info(std::string msg)
{
    Logger::getInstance().consoleWrite(msg, LogLevel::INFO);
}

/**
 * @brief Alias for logging messages with "OK" status
 * @param msg Message to be logged (without line breaks)
 */
void Logger::Logger::ok(std::string msg)
{
    Logger::getInstance().consoleWrite(msg, LogLevel::OK);
}

/**
 * @brief Alias for logging plain text rows
 * @param msg Message to be logged (without line breaks)
 */
void Logger::Logger::text(std::string msg)
{
    Logger::getInstance().consoleWrite(msg, LogLevel::TEXT);
}

/**
 * @brief Alias for logging debugging informations
 * @param msg Message to be logged (without line breaks)
 */
void Logger::Logger::debug(std::string msg)
{
    Logger::getInstance().consoleWrite(msg, LogLevel::DEBUG);
}

/**
 * @brief Ctor
 */
Logger::Logger::Logger()
{

}

/**
 * @brief Inside function used to write to STDOUT
 * @param msg Message to be logged (without line breaks)
 * @param level Log level from loglevel.h enum
 */
void Logger::Logger::consoleWrite(std::string msg, LogLevel level)
{
    this->writeTag(level, true);
    std::cout << msg << std::endl;
}

/**
 * @brief Change foreground text color, works only in UNIX console with ANSI codes
 * @param level Log level from loglevel.h enum - color depends on it
 */
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

/**
 * @brief Resets console foreground text color, works only in UNIX console with ANSI codes
 */
void Logger::Logger::resetColor()
{
    #ifdef __linux__

    std::cout << "\033[0m";

    #endif
}

/**
 * @brief Writes tag before log message
 * @param level Log level from loglevel.h enum
 * @param colors Enables colors, available only in UNIX consoles with ANSI codes
 */
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
