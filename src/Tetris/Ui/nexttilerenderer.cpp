#include "include/Tetris/Ui/nexttilerenderer.h"

/**
 * @brief Ctor
 * @param engine Graphics engine, should be already initialized
 */
Tetris::Ui::NextTileRenderer::NextTileRenderer(std::shared_ptr<Gfx::Engine> engine, SDL_Rect area)
    : engine(engine), area(area)
{

}

/**
 * @brief Draw new tile in next tile area
 * @param tile
 */
void Tetris::Ui::NextTileRenderer::render(std::shared_ptr<Tetris::Tile> tile)
{
    SDL_Color *red = new SDL_Color;
    red->r = 255;
    red->g = 0;
    red->b = 0;
    this->engine->drawRect(this->area, red, true);
    delete red;
}
