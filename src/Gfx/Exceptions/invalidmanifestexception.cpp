#include "include/Gfx/Exceptions/invalidmanifestexception.h"

const char *Gfx::Exceptions::InvalidManifestException::what() const throw()
{
    return "Unable to load, read or parse Manifest.txt file";
}
