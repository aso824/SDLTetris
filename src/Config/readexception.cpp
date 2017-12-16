#include "include/Config/readexception.h"

const char *Config::ReadException::what() const throw()
{
    return "Can't find or read configuration file.";
}
