#include "include/Gfx/Exceptions/unknownfontexception.h"

Gfx::Exceptions::UnknownFontException::UnknownFontException(std::string fontName)
{
    this->name = fontName;
}

const char *Gfx::Exceptions::UnknownFontException::what() const throw()
{
    return std::string(std::string("Can't find font ") + this->name + std::string(" in dictionary.")).c_str();
}
