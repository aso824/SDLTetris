#ifndef GAMEUI_H
#define GAMEUI_H

#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "nexttilerenderer.h"
#include "include/Tetris/tile.h"
#include "include/Tetris/player.h"
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

                void setPlayer(std::shared_ptr<Player> player);

            protected:
                std::shared_ptr<Gfx::Engine> engine;
                std::shared_ptr<Gfx::TextWriter> writer;
                std::unique_ptr<NextTileRenderer> nextTileRenderer;
                std::shared_ptr<Player> player;

                SDL_Rect area;
                SDL_Rect nextTileArea;

                const int padding = 25;
                const int shading = 64;

                void drawShadedBoxFrame(SDL_Rect rect);

                SDL_Rect calcTilesArea();
                SDL_Rect calcSidebarArea();
                SDL_Rect calcNextTileArea();

                void clearTilesArea();

                SDL_Point writeNextTileLabel();
                SDL_Point writePoints();
                SDL_Point writeLevel(SDL_Point writePointsLabelPosition);

                std::string formatPoints(unsigned int points);
        };
    }
}


#endif // GAMEUI_H
