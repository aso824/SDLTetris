#ifndef MAPRENDERER_H
#define MAPRENDERER_H

#include <memory>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "map.h"
#include "enums.h"
#include "tile.h"
#include "blockdrawer.h"
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
            void drawTile(std::shared_ptr<Tile> t);

        protected:
            std::shared_ptr<Gfx::Engine> engine;
            std::shared_ptr<Map> map;
            std::unique_ptr<BlockDrawer> blockDrawer;

            SDL_Rect area;

            void clearTileArea();
    };
}

#endif // MAPRENDERER_H
