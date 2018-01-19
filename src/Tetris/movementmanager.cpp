#include "include/Tetris/movementmanager.h"

/**
 * @brief Ctor
 * @param map Game map pointer
 */
Tetris::MovementManager::MovementManager(std::shared_ptr<Tetris::Map> map)
{
    this->map = map;
    this->currentSpeed = Globals::blockSpeedStart;
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
    bool hadCollision = this->iterateOverCheckers(tile);

    // Undo move
    this->undoMove(tile, direction);

    // Return result
    return hadCollision;
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
 * @brief Check given rotation direction for tile against all registered Collision Checkers
 * @param tile Tile to be checked
 * @param direction Desired direction
 * @return True if move is possible, else false
 */
bool Tetris::MovementManager::isRotationPossible(std::shared_ptr<Tetris::Tile> tile, Tetris::RotationDirection direction)
{
    // Nothing to check
    if (this->collisionCheckers.size() == 0)
        return true;

    // Make move (will be reversed)
    tile->rotate(direction);

    // Check collisions
    bool hadCollision = this->iterateOverCheckers(tile);

    // Undo move
    this->undoRotation(tile, direction);

    // Return result
    return hadCollision;
}

/**
 * @brief Try to make Tile rotation in given direction
 * @param tile Tile to be checked and rotated
 * @param direction Desired direction
 * @return True if Tile was rotated, false if any CollisionChecker denied rotation in given direction
 */
bool Tetris::MovementManager::makeRotation(std::shared_ptr<Tetris::Tile> tile, Tetris::RotationDirection direction)
{
    if (this->isRotationPossible(tile, direction)) {
        tile->rotate(direction);
        return true;
    }

    return false;
}

/**
 * @brief Call this function on each loop iteration to make tile autofalling
 * @param tile Tile to be moved
 */
bool Tetris::MovementManager::tick(std::shared_ptr<Tetris::Tile> tile)
{
    if (lastTick == 0) {
        lastTick = SDL_GetTicks();
        return true;
    }

    if (SDL_GetTicks() - lastTick > this->currentSpeed) {
        this->lastTick = SDL_GetTicks();
        return this->makeMove(tile, MOVE_DOWN);
    }

    return true;
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

/**
 * @brief Make rotation on tile in opposite direction
 * @param tile Tile to be rotated
 * @param direction Original direction to be inverted
 */
void Tetris::MovementManager::undoRotation(std::shared_ptr<Tetris::Tile> tile, Tetris::RotationDirection direction)
{
    if (direction == ROTATE_LEFT) {
        tile->rotateRight();
    } else if (direction == ROTATE_RIGHT) {
        tile->rotateLeft();
    }
}

/**
 * @brief Check current Tile position against all registered checkers
 * @param tile Tile to be checked
 * @return False if any checker returned false, true only if all checkers returned true
 */
bool Tetris::MovementManager::iterateOverCheckers(std::shared_ptr<Tetris::Tile> tile)
{
    for (auto &it: this->collisionCheckers) {
        if (it->isCurrentPositionCorrect(tile) == false) {
            return false;
        }
    }

    return true;
}
