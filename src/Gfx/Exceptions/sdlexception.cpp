#include "include/Gfx/Exceptions/sdlexception.h"

const char *Gfx::Exceptions::SDLException::what() const throw()
{
    return std::string("Error while " + this->m_message + ", SDL Error: " + std::string(SDL_GetError())).c_str();
}
