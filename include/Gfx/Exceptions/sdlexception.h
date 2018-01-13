#ifndef SDLEXCEPTION_H
#define SDLEXCEPTION_H

#include <SDL2/SDL.h>
#include <string>

namespace Gfx {
    namespace Exceptions {
        class SDLException : public std::exception
        {
            public:
                SDLException(std::string msg) : m_message(msg) { }
                virtual const char* what() const throw();

            protected:
                std::string m_message;
        };
    }
}

#endif // SDLEXCEPTION_H
