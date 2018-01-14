#include "include/Tetris/maprenderer.h"

/**
 * @brief Ctor
 * @param engine Already initialized Gfx::Engine instance
 * @param map Game map object
 * @param area Rect where tiles will be rendered, must be in 1:2 proportions
 */
Tetris::MapRenderer::MapRenderer(std::shared_ptr<Gfx::Engine> engine, std::shared_ptr<Map> map, SDL_Rect area)
{
    this->engine = engine;
    this->map = map;
    this->area = area;
    this->tileSize = this->calculateTileSize();
}

/**
 * @brief Dtor
 */
Tetris::MapRenderer::~MapRenderer()
{

}

/**
 * @brief Tetris::MapRenderer::render
 */
void Tetris::MapRenderer::render()
{
    for (int i = 1; i <= 10; i++) {
        this->drawBlock(TileColors(i % 7 + 1), {326 + this->tileSize * (i - 1), 25});
    }
}

/**
 * @brief Calculate tile size, depends on given area
 * @return Tile size in pixels
 * @throws Tetris::Exceptions::InvalidGeometry when ratio isn't 1:2
 */
int Tetris::MapRenderer::calculateTileSize()
{
    float ratio = (float)this->area.w / (float)this->area.h;
    if (ratio != 0.5) {
        Logger::Logger::debug(std::string("calculateTileSize(): game area resolution: (")
                             + std::to_string(this->area.w)
                             + std::string(", ")
                             + std::to_string(this->area.h)
                             + std::string("), ratio ")
                             + std::to_string(ratio)
                             + std::string(" (expected 0.5)"));

        throw std::logic_error("Game area resolution ratio is invalid");
    }

    return this->area.w / 10;
}

/**
 * @brief Draw single block on map
 * @param color Color of block to be drawn
 * @param position Block position, in map coordinates
 */
void Tetris::MapRenderer::drawBlock(TileColors color, int x, int y)
{
    this->drawBlock(color, {x, y});
}

/**
 * @brief Draw single block on screen
 * @param color Color of block to be drawn
 * @param p Block position, raw (on screen)
 */
void Tetris::MapRenderer::drawBlock(TileColors color, SDL_Point p)
{
    if (color == TILE_COLOR_BLANK)
        return;

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

    this->engine->renderTexture(assetName, p);
}
