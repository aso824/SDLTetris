#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>

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

            inline unsigned int getScreenWidth() { return this->screenWidth; }
            inline unsigned int getScreenHeight() { return this->screenHeight; }

            void clearScreen();
            void refresh();

            void drawRect(SDL_Rect rect, SDL_Color* color = nullptr, bool filled = false);

        protected:
            SDL_Window* win;
            SDL_Renderer* ren;
            unsigned int screenWidth;
            unsigned int screenHeight;

            void initAll();
            void destroyAll();
    };
}

#endif // ENGINE_H
