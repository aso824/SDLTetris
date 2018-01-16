#ifndef ABSTRACTCOLLISIONCHECKER_H
#define ABSTRACTCOLLISIONCHECKER_H

#include <memory>
#include "include/Tetris/tile.h"
#include "include/Tetris/enums.h"

namespace Tetris {
    namespace Collisions {
        class AbstractCollisionChecker
        {
            public:
                AbstractCollisionChecker() = delete;
                virtual bool isCurrentPositionCorrect(std::shared_ptr<Tile> tile) = 0;
        };
    }
}

#endif // ABSTRACTCOLLISIONCHECKER_H
