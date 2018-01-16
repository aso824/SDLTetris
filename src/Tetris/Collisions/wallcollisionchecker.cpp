#include "include/Tetris/Collisions/wallcollisionchecker.h"

/**
 * @brief Check collision between Tile and walls
 * @param tile Pointer to Tile object, already moved, to be checked
 * @return False if position is invalid, else true
 */
bool Tetris::Collisions::WallCollisionChecker::isCurrentPositionCorrect(std::shared_ptr<Tile> tile)
{
    SDL_Rect rect = tile->getRect();

    // Left wall
    if (rect.x < 0) {
        return false;
    }

    // Right wall
    if (rect.x > 10 - rect.w) {
        return false;
    }

    // Floor
    if (rect.y > 20 - rect.h) {
        return false;
    }

    // No errors found
    return true;
}
