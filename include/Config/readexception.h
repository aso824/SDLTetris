#ifndef READEXCEPTION_H
#define READEXCEPTION_H

#include <exception>

namespace Config {
    class ReadException : public std::exception
    {
    public:
        virtual const char* what() const throw();
    };
}

#endif // READEXCEPTION_H
