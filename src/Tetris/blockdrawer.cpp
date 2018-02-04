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
void Tetris::BlockDrawer::setBlockSize(float size)
{
    this->blockSize = size;
}

/**
 * @brief Get current block size
 * @return Current block size in pixels
 */
float Tetris::BlockDrawer::getBlockSize()
{
    return this->blockSize;
}

/**
 * @brief Set area where tiles will be drawed by grid coordinates
 * @param area SDL_Rect with correct XY position and WH dimensions on screen
 * @param rows Count of rows in blocks grid
 * @param columns Count of columns in blocks grid
 * @throws std::logic_error When ratio is not 1:1
 */
void Tetris::BlockDrawer::setArea(SDL_Rect area, unsigned short rows, unsigned short columns)
{
    if (area.w / columns != area.h / rows) {
        throw std::logic_error("BlockDrawer::setArea: invalid dimensions");
    }

    this->area = area;
    this->rows = rows;
    this->columns = columns;

    this->blockSize = static_cast<float>(area.w) / static_cast<float>(columns);
}

/**
 * @brief Draw block on screen at desired position
 * @param blockColor Block color, must not be TILE_COLOR_BLANK
 * @param p Place where block will be drawed on screen
 * @throws std::logic_error When block size is not set (equals to 0)
 */
void Tetris::BlockDrawer::drawBlock(Tetris::TileColors color, SDL_Point p)
{
    if (color == TILE_COLOR_BLANK) {
        return;
    }

    if (this->blockSize == 0) {
        throw std::logic_error("BlockDrawer::drawBlock: invalid block size");
    }

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

/**
 * @brief Draw block on screen
 * @param color Block color, must not be TILE_COLOR_BLANK
 * @param x Block position on grid, columns
 * @param y Block position on grid, rows
 */
void Tetris::BlockDrawer::drawBlock(Tetris::TileColors color, unsigned short x, unsigned short y)
{
    if (y >= this->rows || x >= this->columns) {
        return;
    }

    SDL_Point pos = {
        this->area.x + this->blockSize * x,
        this->area.y + this->blockSize * y
    };

    this->drawBlock(color, pos);
}
