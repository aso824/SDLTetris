#include "include/Tetris/Ui/nexttilerenderer.h"

/**
 * @brief Ctor
 * @param engine Graphics engine, should be already initialized
 */
Tetris::Ui::NextTileRenderer::NextTileRenderer(std::shared_ptr<Gfx::Engine> engine, SDL_Rect area)
    : engine(engine), area(area)
{
    this->setBlockSize();
}

/**
 * @brief Draw new tile in next tile area
 * @param tile
 */
void Tetris::Ui::NextTileRenderer::render(std::shared_ptr<Tetris::Tile> tile)
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            this->drawBlock(TileColors((i * j) % 7 + 1), i, j);
        }
    }
}

/**
 * @brief Calculate and set the block size, depends of area to render
 * @throws std::logic_error When w/h != 1 (invalid ratio, must be 1:1)
 */
void Tetris::Ui::NextTileRenderer::setBlockSize()
{
    if (this->area.w != this->area.h) {
        throw std::logic_error("Next tile area resolution ratio is invalid");
    }

    this->blockSize = this->area.w / this->gridSize;
}

/**
 * @brief Draw block in next tile area at desired position
 * @param color Block color to be drawn
 * @param x X-coordinate in GRID COORDINATES
 * @param y Y-coordinate in GRID COORDINATES
 */
void Tetris::Ui::NextTileRenderer::drawBlock(Tetris::TileColors color, int x, int y)
{
    if (x < 0 || x >= this->gridSize || y < 0 || y > this->gridSize) {
        return;
    }

    SDL_Point pos = {
        this->area.x + x * this->blockSize,
        this->area.y + y * this->blockSize
    };

    this->drawBlock(color, pos);
}

/**
 * @brief Draw block in next tile area at desired position
 * @param color Block color to be drawn
 * @param p Block position, in GRAPHICS COORDINATES
 */
void Tetris::Ui::NextTileRenderer::drawBlock(Tetris::TileColors color, SDL_Point p)
{
    // Color names (prefixes) in asset
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
