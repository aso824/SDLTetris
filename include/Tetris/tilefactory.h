#ifndef TILEFACTORY_H
#define TILEFACTORY_H

#include <random>
#include <memory>
#include <SDL2/SDL.h>
#include "tile.h"
#include "enums.h"

namespace Tetris {
    class TileFactory
    {
        public:
            Tile* getRandomTile();
            std::shared_ptr<Tile> getRandomTileSharedPtr();

        protected:
            std::random_device rd;
            TileType lastType;

            TileType getRandomType();
            void setTilePosition(Tile* tile);
    };
}

#endif // TILEFACTORY_H
