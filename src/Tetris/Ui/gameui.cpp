#include "include/Tetris/Ui/gameui.h"

/**
 * @brief Ctor
 * @param engine Graphics engine, should be already initialized
 */
Tetris::Ui::GameUi::GameUi(std::shared_ptr<Gfx::Engine> engine, SDL_Rect area) : engine(engine), area(area)
{
    // Calculate rect for tiles
    this->tilesArea = {
        area.x + padding,
        area.y + padding,
        (area.w - 2 * padding) / 3 * 2,
        area.h - 2 * padding
    };

    // Calculate rect for next tile area
    this->nextTileArea = {
        area.w - (2 * padding) - ((area.w / 3) / 2) + area.x,
        area.y + padding * 3,
        (area.w / 3) - 2 * padding,
        (area.w / 3) - 2 * padding
    };
}

/**
 * @brief Draws main game UI like box for tiles and all other things
 */
void Tetris::Ui::GameUi::draw()
{
    // For debugging
    SDL_Color red = {255, 0, 0, 0};
    this->engine->drawRect(area, &red);

    // Color shading
    const int shading = 64;
    SDL_Color color = {255, 255, 255, 0};

    for (int i = 1; i < 5; i++) {
        // Game tiles area
        this->engine->drawRect({
                                   this->tilesArea.x - i,
                                   this->tilesArea.y - i,
                                   this->tilesArea.w + i * 2,
                                   this->tilesArea.h + i * 2
                               }, &color);

        // Next tile area
        this->engine->drawRect({
                                   this->nextTileArea.x - i,
                                   this->nextTileArea.y - i,
                                   this->nextTileArea.w + i * 2,
                                   this->nextTileArea.h + i * 2
                               }, &color);

        // Color shading
        color.r -= shading;
        color.g -= shading;
        color.b -= shading;
    }
}
