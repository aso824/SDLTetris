#include "include/Tetris/Collisions/mapcollisionchecker.h"

/**
 * @brief Ctor
 * @param map Tetris map object
 */
Tetris::Collisions::MapCollisionChecker::MapCollisionChecker(std::shared_ptr<Tetris::Map> map)
{
    this->map = map;
}

/**
 * @brief Check collision between Tile and Map blocks
 * @param tile Pointer to Tile object, already moved, to be checked
 * @return False if position is invalid, else true
 */
bool Tetris::Collisions::MapCollisionChecker::isCurrentPositionCorrect(std::shared_ptr<Tetris::Tile> tile)
{
    SDL_Rect dims = tile->getRect();
    TileShape shape = tile->getShape();

    for (int x = 0; x < dims.w; x++) {
        for (int y = 0; y < dims.h; y++) {
            // Skip blank tile blocks
            if (shape[y][x] == TILE_COLOR_BLANK) {
                continue;
            }

            // Map tile block to map
            SDL_Point onMap = {
                dims.x + x,
                dims.y + y
            };

            // Skip blocks out of map range
            if (onMap.x < 0 || onMap.x > 9 || onMap.y < 0 || onMap.y > 19) {
                continue;
            }

            // Check block value on map
            if (this->map->getBlockAt(onMap.x, onMap.y) != TILE_COLOR_BLANK) {
                return false;
            }
        }
    }

    return true;
}
