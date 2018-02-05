#ifndef TEXTWRITER_H
#define TEXTWRITER_H

#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "engine.h"
#include "fontmanager.h"
#include "font.h"

namespace Gfx {
    class TextWriter
    {
        public:
            TextWriter(std::shared_ptr<Engine> const& engine);
            void writeText(std::string s, Font f, SDL_Point pos, SDL_Color color, int width = 0, bool centered = false);
            void writeText(std::string s, std::string fontName, int size, SDL_Point pos, SDL_Color color, int width = 0, bool centered = false);

        protected:
            std::shared_ptr<Engine> engine;
            std::shared_ptr<FontManager> fontmgr;
    };
}

#endif // TEXTWRITER_H
