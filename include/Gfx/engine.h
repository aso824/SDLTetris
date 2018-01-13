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

        protected:
            SDL_Window* win;
            SDL_Renderer* ren;

            void initAll();
            void destroyAll();
    };
}

#endif // ENGINE_H
