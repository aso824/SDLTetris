#ifndef MOVEMENTMANAGER_H
#define MOVEMENTMANAGER_H

#include <memory>
#include <vector>
#include "tile.h"
#include "enums.h"
#include "map.h"
#include "Collisions/abstractcollisionchecker.h"

namespace Tetris {
    class MovementManager
    {
        public:
            MovementManager(std::shared_ptr<Map> map);
            void addCollisionChecker(std::shared_ptr<Collisions::AbstractCollisionChecker> checker);
            bool isMovePossible(std::shared_ptr<Tile> tile, MovementDirection direction);
            bool makeMove(std::shared_ptr<Tile> tile, MovementDirection direction);

        protected:
            std::shared_ptr<Map> map;
            std::vector<std::shared_ptr<Collisions::AbstractCollisionChecker>> collisionCheckers;

            void undoMove(std::shared_ptr<Tile> tile, MovementDirection direction);
    };
}

#endif // MOVEMENTMANAGER_H
