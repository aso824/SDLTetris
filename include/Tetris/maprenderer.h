#ifndef MAPRENDERER_H
#define MAPRENDERER_H

#include <memory>
#include <SDL2/SDL.h>
#include "map.h"
#include "include/Gfx/engine.h"

namespace Tetris {
    class MapRenderer
    {
        public:
            MapRenderer(
                    std::shared_ptr<Gfx::Engine> engine,
                    std::shared_ptr<Map> map,
                    SDL_Rect area
            );

            void render();

        protected:
            std::shared_ptr<Gfx::Engine> engine;
            std::shared_ptr<Map> map;
            SDL_Rect area;
    };
}

#endif // MAPRENDERER_H
