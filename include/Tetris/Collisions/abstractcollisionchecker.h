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
                virtual ~AbstractCollisionChecker() { }
                virtual bool isCurrentPositionCorrect(std::shared_ptr<Tile> tile) = 0;

            protected:
                AbstractCollisionChecker() { }
        };
    }
}

#endif // ABSTRACTCOLLISIONCHECKER_H
