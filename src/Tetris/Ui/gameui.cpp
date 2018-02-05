#include "include/Tetris/Ui/gameui.h"

/**
 * @brief Ctor
 * @param engine Graphics engine, should be already initialized
 */
Tetris::Ui::GameUi::GameUi(std::shared_ptr<Gfx::Engine> engine, SDL_Rect area) : engine(engine), area(area)
{
    this->writer = std::unique_ptr<Gfx::TextWriter>(new Gfx::TextWriter(engine));
    this->nextTileRenderer = std::unique_ptr<NextTileRenderer>(new NextTileRenderer(engine, this->calcNextTileArea()));
}

/**
 * @brief Dtor
 */
Tetris::Ui::GameUi::~GameUi()
{

}

/**
 * @brief Get area for rendering tiles
 * @return Rect with dimensions
 */
SDL_Rect Tetris::Ui::GameUi::getTilesArea()
{
    return this->calcTilesArea();
}

/**
 * @brief Draws main game UI like box for tiles and all other things
 */
void Tetris::Ui::GameUi::draw()
{
    // Frames
    this->drawTilesFrame();
    this->drawShadedBoxFrame(this->nextTileArea);

    // Sidebar labels and values
    SDL_Point p;
    p = this->writeNextTileLabel();
    p = this->writePointsLabel();
    p = this->writeLevelLabel(p);
}

/**
 * @brief Draw frame around tiles area
 */
void Tetris::Ui::GameUi::drawTilesFrame()
{
    this->drawShadedBoxFrame(this->calcTilesArea());
}

/**
 * @brief Tetris::Ui::GameUi::drawNextTile
 * @param tile
 */
void Tetris::Ui::GameUi::drawNextTile(std::shared_ptr<Tetris::Tile> tile)
{
    this->nextTileRenderer->render(tile);
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
            (int)((area.h - 2 * this->padding) * 0.5),
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

    SDL_Rect area = {
        sidebarArea.x,
        (int)(sidebarArea.y + sidebarArea.h * 0.1),
        sidebarArea.w,
        sidebarArea.w
    };

    this->nextTileArea = area;

    return area;
}

/**
 * @brief Clear rectangle for tiles
 */
void Tetris::Ui::GameUi::clearTilesArea()
{
    SDL_Color black = {0, 0, 0, 0};
    this->engine->drawRect(this->calcTilesArea(), &black, true);
}

/**
 * @brief Draw a label for next tile in sidebar
 * @return Position of label
 */
SDL_Point Tetris::Ui::GameUi::writeNextTileLabel()
{
    SDL_Point pos = {
        this->nextTileArea.x,
        (int)(this->nextTileArea.y - this->nextTileArea.w * 0.4)
    };

    this->writer->writeText("Następny:", "Roboto", 48, pos, {255, 255, 255, 255}, this->nextTileArea.w);

    return pos;
}

/**
 * @brief Draw a label for points in sidebar
 * @return Position of label
 */
SDL_Point Tetris::Ui::GameUi::writePointsLabel()
{
    SDL_Point pos = {
        this->nextTileArea.x,
        (int)(this->nextTileArea.y + this->nextTileArea.w * 1.1)
    };

    this->writer->writeText("Punkty:", "Roboto", 48, pos, {255, 255, 255, 255}, this->nextTileArea.w * 0.8);

    return pos;
}

/**
 * @brief Draw a label for level in sidebar
 * @return Position of label
 */
SDL_Point Tetris::Ui::GameUi::writeLevelLabel(SDL_Point pointsLabelPosition)
{
    SDL_Point pos = {
        pointsLabelPosition.x,
        (int)(pointsLabelPosition.y * 1.6)
    };

    this->writer->writeText("Poziom:", "Roboto", 48, pos, {255, 255, 255, 255}, this->nextTileArea.w * 0.8);

    return pos;
}
