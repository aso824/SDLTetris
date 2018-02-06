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
#include "movementmanager.h"
#include "player.h"
#include "Collisions/wallcollisionchecker.h"
#include "Collisions/mapcollisionchecker.h"

namespace Tetris {
    class Game
    {
        public:
            Game();

            void setGraphicsEngine(std::shared_ptr<Gfx::Engine> engine);
            void start();

        protected:
            std::shared_ptr<Gfx::Engine> engine;
            std::unique_ptr<Ui::GameUi> ui;
            std::shared_ptr<Map> map;
            std::shared_ptr<MapRenderer> mapRen;
            std::shared_ptr<Tile> currentTile, nextTile;
            TileFactory tileFactory;
            std::unique_ptr<MovementManager> movementMgr;
            std::shared_ptr<Player> player;

            SDL_Rect getMainGameRect();
            void createNextTile();
    };
}

#endif // GAME_H
