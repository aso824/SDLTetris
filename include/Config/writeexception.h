#ifndef WRITEEXCEPTION_H
#define WRITEEXCEPTION_H

#include <exception>

namespace Config {
    class WriteException : public std::exception
    {
    public:
        virtual const char* what() const throw();
    };
}
#endif // WRITEEXCEPTION_H
