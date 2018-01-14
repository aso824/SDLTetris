#ifndef GAME_H
#define GAME_H

#include <memory>
#include <SDL2/SDL.h>
#include "include/Gfx/engine.h"
#include "Ui/gameui.h"
#include "tile.h"
#include "map.h"

namespace Tetris {
    class Game
    {
        public:
            ~Game();

            void setGraphicsEngine(std::shared_ptr<Gfx::Engine> engine);
            void start();

        protected:
            std::shared_ptr<Gfx::Engine> engine;
            std::unique_ptr<Ui::GameUi> ui;

            SDL_Rect getMainGameRect();
    };
}

#endif // GAME_H
