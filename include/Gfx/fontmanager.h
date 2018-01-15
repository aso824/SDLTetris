#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "include/Gfx/font.h"
#include "include/Gfx/Exceptions/unknownfontexception.h"

namespace Gfx {
    class FontManager
    {
        public:
            FontManager();
            ~FontManager();

            void addFont(std::string fontName, std::string filename);
            Font getFont(std::string fontName, int size);
            void clearCache();

        protected:
            std::unique_ptr<std::map<std::string, std::string>> fontFiles;
            std::unique_ptr<std::vector<Font>> fonts;

            bool isFontExistInDictionary(std::string fontName);
            Gfx::Font loadFont(std::string fontName, int size);
    };
}

#endif // FONTMANAGER_H
