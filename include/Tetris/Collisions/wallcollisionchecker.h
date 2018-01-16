#ifndef WALLCOLLISIONCHECKER_H
#define WALLCOLLISIONCHECKER_H

#include <memory>
#include "abstractcollisionchecker.h"
#include "include/Tetris/tile.h"
#include "include/Tetris/enums.h"

namespace Tetris {
    namespace Collisions {
        class WallCollisionChecker : public AbstractCollisionChecker
        {
            public:
                WallCollisionChecker() { }
                ~WallCollisionChecker() { }
                bool isCurrentPositionCorrect(std::shared_ptr<Tile> tile);
        };
    }
}


#endif // WALLCOLLISIONCHECKER_H
