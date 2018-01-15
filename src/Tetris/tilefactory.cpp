#include "include/Tetris/tilefactory.h"

/**
 * @brief Random tile generator
 * @return Generated Tetris::Tile object pointer, with ownership
 */
Tetris::Tile* Tetris::TileFactory::getRandomTile()
{
    TileType type = this->getRandomType();
    Tile* tile = new Tile(type, {0, 0});
    this->setTilePosition(tile);

    return tile;
}

/**
 * @brief Random tile generator
 * @return Generated Tetris::Tile object pointer, inside std::shared_ptr
 */
std::shared_ptr<Tetris::Tile> Tetris::TileFactory::getRandomTileSharedPtr()
{
    return std::shared_ptr<Tetris::Tile>(this->getRandomTile());
}

/**
 * @brief Generate random tile type, using MT19937 PRNG
 * @return Tile type
 */
Tetris::TileType Tetris::TileFactory::getRandomType()
{
    // 0 to 6 distribution
    std::uniform_int_distribution<int> dist(0, 6 + 1);

    std::mt19937 mt(this->rd());
    return TileType(dist(mt));
}

/**
 * @brief Set tile starting position
 * @param tile Tile pointer to be modified
 */
void Tetris::TileFactory::setTilePosition(Tetris::Tile* tile)
{
    // Set position to (0, 0) at start
    SDL_Point pos = {0, 0};

    // Place tile in the middle of screen in X axis
    int tileWidth = tile->getWidth();
    pos.x = static_cast<int>(10.f / 2.f - (float)tileWidth / 2.f);

    // Place tile above map in Y axis
    pos.y = 0 - tile->getHeight();

    tile->setPosition(pos);
}

