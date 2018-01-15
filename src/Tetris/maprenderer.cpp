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
 * @brief Render static map (from data vector)
 */
void Tetris::MapRenderer::render()
{
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            this->drawBlock(this->map->getData()->at(i).at(j), {j, i});
        }
    }
}

/**
 * @brief Draw dynamic tile on map
 * @param t Tile to be drawn
 */
void Tetris::MapRenderer::drawTile(std::shared_ptr<Tetris::Tile> t)
{
    SDL_Point pos = t->getPosition();

    for (int y = 0; y < t->getHeight(); y++) {
        for (int x = 0; x < t->getWidth(); x++) {
            if (t->getShape().at(y).at(x) == true) {
                this->drawBlock(t->getColor(), {pos.x + x, pos.y + y});
            }
        }
    }
}

/**
 * @brief Calculate tile size, depends on given area
 * @return Tile size in pixels
 * @throws Tetris::Exceptions::InvalidGeometry when ratio isn't 1:2
 */
float Tetris::MapRenderer::calculateTileSize()
{
    float ratio = (float)this->area.w / (float)this->area.h;
    if (ratio != 0.5) {
        // Some debug info on fail
        Logger::Logger::debug(std::string("calculateTileSize(): game area resolution: (")
                             + std::to_string(this->area.w)
                             + std::string(", ")
                             + std::to_string(this->area.h)
                             + std::string("), ratio ")
                             + std::to_string(ratio)
                             + std::string(" (expected 0.5)"));

        throw std::logic_error("Game area resolution ratio is invalid");
    }

    return (float)this->area.w / 10.f;
}

/**
 * @brief Draw single block on map
 * @param color Color of block to be drawn
 * @param position Block position, in map coordinates
 */
void Tetris::MapRenderer::drawBlock(TileColors color, SDL_Point p)
{
    // Don't draw blank block
    if (color == TILE_COLOR_BLANK)
        return;

    // Don't draw block outside map
    if (p.x < 0 || p.x > 9 || p.y < 0 || p.y > 19)
        return;

    int x = this->area.x + this->tileSize * p.x;
    int y = this->area.y + this->tileSize * p.y;

    this->drawBlock(color, x, y);
}

/**
 * @brief Draw single block on screen
 * @param color Color of block to be drawn
 * @param p Block position, raw (on screen)
 */
void Tetris::MapRenderer::drawBlock(TileColors color, int x, int y)
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

    this->engine->renderTexture(assetName, {x, y});
}
