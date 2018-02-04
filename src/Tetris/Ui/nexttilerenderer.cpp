#include "include/Tetris/Ui/nexttilerenderer.h"

/**
 * @brief Ctor
 * @param engine Graphics engine, should be already initialized
 */
Tetris::Ui::NextTileRenderer::NextTileRenderer(std::shared_ptr<Gfx::Engine> engine, SDL_Rect area)
    : engine(engine), area(area)
{
    this->setBlockSize();

    this->drawer = std::unique_ptr<BlockDrawer>(new BlockDrawer(engine));
    this->drawer->setBlockSize(this->blockSize);
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

                this->drawer->drawBlock(tile->getColor(), blockPosition);
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
 * @brief Clear next tile area
 */
void Tetris::Ui::NextTileRenderer::clearArea()
{
    this->engine->clearRect(this->area);
}
