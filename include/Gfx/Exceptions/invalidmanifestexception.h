#ifndef INVALIDMANIFESTEXCEPTION_H
#define INVALIDMANIFESTEXCEPTION_H

#include <string>

namespace Gfx {
    namespace Exceptions {
        class InvalidManifestException
        {
            public:
                virtual const char* what() const throw();
        };
    }
}

#endif // INVALIDMANIFESTEXCEPTION_H
