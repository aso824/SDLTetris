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

    // Calculate rect for sidebar
    this->sidebarArea = {
        this->tilesArea.w + area.x + padding * 2,
        this->tilesArea.y,
        area.w - this->tilesArea.w - 3 * padding,
        this->tilesArea.h
    };
}

/**
 * @brief Tetris::Ui::GameUi::~GameUi
 */
Tetris::Ui::GameUi::~GameUi()
{

}

/**
 * @brief Draws main game UI like box for tiles and all other things
 */
void Tetris::Ui::GameUi::draw()
{
    // For debugging
    SDL_Color red = {255, 0, 0, 0};
    this->engine->drawRect(area, &red);

    SDL_Color green = {0, 255, 0, 0};
    this->engine->drawRect(this->sidebarArea, &green);

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

        // Color shading
        color.r -= shading;
        color.g -= shading;
        color.b -= shading;
    }
}
