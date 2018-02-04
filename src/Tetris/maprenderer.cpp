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

    this->blockDrawer = std::unique_ptr<BlockDrawer>(new BlockDrawer(this->engine));
    this->blockDrawer->setArea(area, 20, 10);
}

/**
 * @brief Dtor
 */
Tetris::MapRenderer::~MapRenderer()
{

}

/**
 * @brief Render static map (from data vector). Must be called before drawTile()
 */
void Tetris::MapRenderer::render()
{
    this->clearTileArea();

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            this->blockDrawer->drawBlock(this->map->getBlockAt(j, i), j, i);
        }
    }
}

/**
 * @brief Draw dynamic tile on map
 * @param t Tile to be drawn
 */
void Tetris::MapRenderer::drawTile(std::shared_ptr<Tetris::Tile> t)
{
    // Check against invalid tiles
    if (t->getColor() == TileColors::TILE_COLOR_BLANK) {
        Logger::Logger::warn("Can't draw blank tile!");
        return;
    }

    SDL_Point pos = t->getPosition();

    for (int y = 0; y < t->getHeight(); y++) {
        for (int x = 0; x < t->getWidth(); x++) {
            if (t->getShape().at(y).at(x) == true) {
                this->blockDrawer->drawBlock(t->getColor(), pos.x + x, pos.y + y);
            }
        }
    }
}

/**
 * @brief Clear area used for tiles
 */
void Tetris::MapRenderer::clearTileArea()
{
    this->engine->clearRect(this->area);
}
