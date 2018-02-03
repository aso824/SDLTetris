#ifndef NEXTTILERENDERER_H
#define NEXTTILERENDERER_H

#include <memory>
#include <SDL2/SDL.h>
#include "include/Tetris/tile.h"
#include "include/Gfx/engine.h"

namespace Tetris {
    namespace Ui {
        class NextTileRenderer
        {
            public:
                NextTileRenderer(std::shared_ptr<Gfx::Engine> engine, SDL_Rect area);
                void render(std::shared_ptr<Tetris::Tile> tile);

            protected:
                std::shared_ptr<Gfx::Engine> engine;
                SDL_Rect area;
        };
    }
}


#endif // NEXTTILERENDERER_H
