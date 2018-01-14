#include "include/Tetris/Ui/gameui.h"

/**
 * @brief Ctor
 * @param engine Graphics engine, should be already initialized
 */
Tetris::Ui::GameUi::GameUi(std::shared_ptr<Gfx::Engine> engine, SDL_Rect area) : engine(engine), area(area)
{

}

/**
 * @brief Dtor
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
    //SDL_Color green = {0, 255, 0, 0};
    //this->engine->drawRect(this->sidebarArea, &green);

    this->drawShadedBoxFrame(this->calcTilesArea());

    try {
        TTF_Font* font = this->engine->getFontManager()->getFont("Roboto", 14).fontObj;
        SDL_Surface *surf = TTF_RenderUTF8_Blended(font, "Następny:", {255, 255, 255, 255});
        SDL_Texture *tex = SDL_CreateTextureFromSurface(this->engine->getRenderer(), surf);
        SDL_Rect dst = {715, 60, 150, 30};
        SDL_RenderCopy(this->engine->getRenderer(), tex, NULL, &dst);

        SDL_FreeSurface(surf);
        SDL_DestroyTexture(tex);
    } catch (Gfx::Exceptions::UnknownFontException &e) {
        //Logger::Logger::warn(e.what());
    }

    this->drawShadedBoxFrame(this->calcNextTileArea());
}

/**
 * @brief Draw shaded box frame around given rect
 * @param rect Area to be framed
 */
void Tetris::Ui::GameUi::drawShadedBoxFrame(SDL_Rect rect)
{
    SDL_Color color = {255, 255, 255, 0};

    for (int i = 1; i < 5; i++) {
        // Box shade
        rect.x--;
        rect.y--;
        rect.w += 2;
        rect.h += 2;

        this->engine->drawRect(rect, &color);

        // Color shading
        color.r -= shading;
        color.g -= shading;
        color.b -= shading;
    }
}

/**
 * @brief Calculate rect for tiles
 * @return
 */
SDL_Rect Tetris::Ui::GameUi::calcTilesArea()
{
    return {
        area.x + this->padding,
        area.y + this->padding,
        (area.w - 2 * this->padding) / 3 * 2,
        area.h - 2 * this->padding
    };
}

/**
 * @brief Calculate rect for whole sidebar
 * @return
 */
SDL_Rect Tetris::Ui::GameUi::calcSidebarArea()
{
    SDL_Rect tilesArea = this->calcTilesArea();

    return {
            tilesArea.w + this->area.x + padding * 2,
            tilesArea.y,
            this->area.w - tilesArea.w - 3 * padding,
            tilesArea.h
    };
}

/**
 * @brief Calculate rect for next tile image
 * @return
 */
SDL_Rect Tetris::Ui::GameUi::calcNextTileArea()
{
    SDL_Rect sidebarArea = this->calcSidebarArea();

    return {
        sidebarArea.x,
        (int)(sidebarArea.y + sidebarArea.h * 0.1),
        sidebarArea.w,
        sidebarArea.w
    };
}

/**
 * @brief Clear rectangle for tiles
 */
void Tetris::Ui::GameUi::clearTilesArea()
{
    SDL_Color black = {0, 0, 0, 0};
    this->engine->drawRect(this->calcTilesArea(), &black, true);
}
