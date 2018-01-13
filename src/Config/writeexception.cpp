#include "include/Config/writeexception.h"

const char *Config::WriteException::what() const throw()
{
    return "Can't write in configuration file.";
}
