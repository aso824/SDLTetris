#include "include/Tetris/blockdrawer.h"

/**
 * @brief Ctor
 * @param engine Graphics engine instance, already initialized
 */
Tetris::BlockDrawer::BlockDrawer(std::shared_ptr<Gfx::Engine> engine)
    : engine(engine)
{

}

/**
 * @brief Set block size to be drawn
 * @param size Size in pixels
 */
void Tetris::BlockDrawer::setBlockSize(unsigned short size)
{
    this->blockSize = size;
}

/**
 * @brief Get current block size
 * @return Current block size in pixels
 */
unsigned short Tetris::BlockDrawer::getBlockSize()
{
    return this->blockSize;
}

/**
 * @brief Draw block on screen at desired position
 * @param blockColor Block color, must not be TILE_COLOR_BLANK
 * @param p Place where block will be drawed on screen
 */
void Tetris::BlockDrawer::drawBlock(Tetris::TileColors color, SDL_Point p)
{
    const std::string names[7] = {
        "yellow",
        "cyan",
        "green",
        "orange",
        "red",
        "purple",
        "blue"
    };

    std::string assetName = "block_" + names[(int)color - 1];

    SDL_Rect dst = {
        p.x,
        p.y,
        static_cast<int>(this->blockSize),
        static_cast<int>(this->blockSize)
    };

    this->engine->renderTexture(assetName, dst);
}
