#ifndef MAPRENDERER_H
#define MAPRENDERER_H

#include <memory>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "map.h"
#include "enums.h"
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
            ~MapRenderer();

            void render();

        protected:
            std::shared_ptr<Gfx::Engine> engine;
            std::shared_ptr<Map> map;
            SDL_Rect area;
            int tileSize;
            SDL_Texture* tilesTexture;

            int calculateTileSize();
            void drawBlock(TileColors color, int x, int y);
            void drawBlock(TileColors color, SDL_Point p);
    };
}

#endif // MAPRENDERER_H
