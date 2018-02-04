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
 * @param tile Tile to be drawn
 */
void Tetris::Ui::NextTileRenderer::render(std::shared_ptr<Tetris::Tile> tile)
{
    this->clearArea();

    int gfxWidth = tile->getWidth() * this->blockSize;
    int gx = this->area.w / 2 - gfxWidth / 2 + this->area.x;

    int gfxHeight = tile->getHeight() * this->blockSize;
    int gy = this->area.h / 2 - gfxHeight / 2 + this->area.y;

    for (int y = 0; y < tile->getHeight(); y++) {
        for (int x = 0; x < tile->getWidth(); x++) {
            if (tile->getShape().at(y).at(x) == true) {
                SDL_Point blockPosition = {
                    gx + x * this->blockSize,
                    gy + y * this->blockSize
                };

                this->drawBlock(tile->getColor(), blockPosition);
            }
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

/**
 * @brief Clear next tile area
 */
void Tetris::Ui::NextTileRenderer::clearArea()
{
    this->engine->clearRect(this->area);
}
