#ifndef UNKNOWNFONTEXCEPTION_H
#define UNKNOWNFONTEXCEPTION_H

#include <string>

namespace Gfx {
    namespace Exceptions {
        class UnknownFontException : public std::exception
        {
            public:
                UnknownFontException(std::string fontName);
                virtual const char* what() const throw();

            private:
                std::string name;
        };
    }
}

#endif // UNKNOWNFONTEXCEPTION_H
