#ifndef GAMEUI_H
#define GAMEUI_H

#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "nexttilerenderer.h"
#include "include/Tetris/tile.h"
#include "include/Gfx/engine.h"
#include "include/Gfx/textwriter.h"

namespace Tetris {
    namespace Ui {
        class GameUi
        {
            public:
                GameUi(std::shared_ptr<Gfx::Engine> engine, SDL_Rect area);
                ~GameUi();

                SDL_Rect getTilesArea();
                void draw();
                void drawTilesFrame();
                void drawNextTile(std::shared_ptr<Tetris::Tile> tile);

            protected:
                std::shared_ptr<Gfx::Engine> engine;
                std::shared_ptr<Gfx::TextWriter> writer;
                std::unique_ptr<NextTileRenderer> nextTileRenderer;

                SDL_Rect area;

                const int padding = 25;
                const int shading = 64;

                void drawShadedBoxFrame(SDL_Rect rect);

                SDL_Rect calcTilesArea();
                SDL_Rect calcSidebarArea();
                SDL_Rect calcNextTileArea();

                void clearTilesArea();
        };
    }
}


#endif // GAMEUI_H
