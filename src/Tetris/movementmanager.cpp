#include "include/Tetris/movementmanager.h"

/**
 * @brief Ctor
 * @param map Game map pointer
 */
Tetris::MovementManager::MovementManager(std::shared_ptr<Tetris::Map> map)
{
    this->map = map;
}

/**
 * @brief Adds collision checker into internal vector to check against it given tile
 * @param checker Children of AbstractCollisionChecker
 */
void Tetris::MovementManager::addCollisionChecker(std::shared_ptr<Tetris::Collisions::AbstractCollisionChecker> checker)
{
    this->collisionCheckers.push_back(checker);
}

/**
 * @brief Check given movement direction for tile against all registered Collision Checkers
 * @param tile Tile to be checked
 * @param direction Desired direction
 * @return True if move is possible, else false
 */
bool Tetris::MovementManager::isMovePossible(std::shared_ptr<Tetris::Tile> tile, Tetris::MovementDirection direction)
{
    // Nothing to check
    if (this->collisionCheckers.size() == 0)
        return true;

    // Make move (will be reversed)
    tile->makeMove(direction);

    // Check collisions
    bool flag = true;

    for (auto &it: this->collisionCheckers) {
        if (it->isCurrentPositionCorrect(tile) == false) {
            flag = false;
        }
    }

    // Undo move
    this->undoMove(tile, direction);

    // Return result
    return flag;
}

/**
 * @brief Try to make Tile move in given direction
 * @param tile Tile to be checked and moved
 * @param direction Desired direction
 * @return True if Tile was moved, false if any CollisionChecker denied move in given direction
 */
bool Tetris::MovementManager::makeMove(std::shared_ptr<Tetris::Tile> tile, Tetris::MovementDirection direction)
{
    if (this->isMovePossible(tile, direction)) {
        tile->makeMove(direction);
        return true;
    }

    return false;
}

/**
 * @brief Make move on tile in opposite direction
 * @param tile Tile to be moved
 * @param direction Original direction to be inverted
 */
void Tetris::MovementManager::undoMove(std::shared_ptr<Tetris::Tile> tile, Tetris::MovementDirection direction)
{
    MovementDirection newDirection;

    switch (direction) {
        case MOVE_LEFT: newDirection = MOVE_RIGHT; break;
        case MOVE_RIGHT: newDirection = MOVE_LEFT; break;
        case MOVE_DOWN: newDirection = MOVE_UP; break;
        case MOVE_UP: newDirection = MOVE_DOWN; break;
    }

    tile->makeMove(newDirection);
}
