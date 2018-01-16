#ifndef MAPCOLLISIONCHECKER_H
#define MAPCOLLISIONCHECKER_H

#include <memory>
#include "abstractcollisionchecker.h"
#include "include/Tetris/tile.h"
#include "include/Tetris/map.h"

namespace Tetris {
    namespace Collisions {
        class MapCollisionChecker : public AbstractCollisionChecker
        {
            public:
                MapCollisionChecker(std::shared_ptr<Tetris::Map> map);
                ~MapCollisionChecker() { }

                bool isCurrentPositionCorrect(std::shared_ptr<Tile> tile);

            protected:
                std::shared_ptr<Tetris::Map> map;
        };
    }
}

#endif // MAPCOLLISIONCHECKER_H
