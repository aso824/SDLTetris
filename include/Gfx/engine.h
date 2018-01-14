#ifndef ENGINE_H
#define ENGINE_H

#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "fontmanager.h"
#include "Exceptions/sdlexception.h"
#include "include/Config/config.h"
#include "include/defaults.h"

namespace Gfx {
    class Engine
    {
        public:
            Engine();
            ~Engine();
            void restart();

            inline SDL_Window* getWindow() { return this->win; }
            inline SDL_Renderer* getRenderer() { return this->ren; }
            inline std::shared_ptr<FontManager> getFontManager() { return this->fontmgr; }

            inline unsigned int getScreenWidth() { return this->screenWidth; }
            inline unsigned int getScreenHeight() { return this->screenHeight; }

            void clearScreen();
            void refresh();

            void drawRect(SDL_Rect rect, SDL_Color* color = nullptr, bool filled = false);

        protected:
            SDL_Window* win = nullptr;
            SDL_Renderer* ren = nullptr;
            unsigned int screenWidth;
            unsigned int screenHeight;
            std::shared_ptr<FontManager> fontmgr;

            void initAll();
            void destroyAll();
    };
}

#endif // ENGINE_H
