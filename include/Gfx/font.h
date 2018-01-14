#ifndef FONT_H
#define FONT_H

#include <string>
#include <SDL2/SDL_ttf.h>

namespace Gfx {
    struct Font {
        std::string name;
        int size;
        TTF_Font* fontObj;
    };
}

#endif // FONT_H
