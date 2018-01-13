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

            void clearScreen();
            void refresh();

        protected:
            SDL_Window* win;
            SDL_Renderer* ren;

            void initAll();
            void destroyAll();
    };
}

#endif // ENGINE_H
