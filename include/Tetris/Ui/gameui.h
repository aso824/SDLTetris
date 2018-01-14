#ifndef GAMEUI_H
#define GAMEUI_H

#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "include/Gfx/engine.h"
#include "include/Gfx/textwriter.h"

namespace Tetris {
    namespace Ui {
        class GameUi
        {
            public:
                GameUi(std::shared_ptr<Gfx::Engine> engine, SDL_Rect area);
                ~GameUi();

                void draw();

            protected:
                std::shared_ptr<Gfx::Engine> engine;
                std::shared_ptr<Gfx::TextWriter> writer;

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
