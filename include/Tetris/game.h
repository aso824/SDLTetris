#ifndef GAME_H
#define GAME_H

#include <memory>
#include <SDL2/SDL.h>
#include "include/Gfx/engine.h"
#include "Ui/gameui.h"
#include "tile.h"
#include "tilefactory.h"
#include "map.h"
#include "maprenderer.h"

namespace Tetris {
    class Game
    {
        public:
            Game();
            ~Game();

            void setGraphicsEngine(std::shared_ptr<Gfx::Engine> engine);
            void start();

        protected:
            std::shared_ptr<Gfx::Engine> engine;
            std::unique_ptr<Ui::GameUi> ui;
            std::shared_ptr<Map> map;
            std::shared_ptr<MapRenderer> mapRen;
            std::shared_ptr<Tile> currentTile;
            TileFactory tileFactory;

            SDL_Rect getMainGameRect();
    };
}

#endif // GAME_H
