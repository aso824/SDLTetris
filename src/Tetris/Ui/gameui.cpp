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
    p = this->writePoints();
    p = this->writeLevel(p);
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
 * @brief Set Player object pointer
 * @param player Shared pointer to Player object
 */
void Tetris::Ui::GameUi::setPlayer(std::shared_ptr<Tetris::Player> player)
{
    this->player = player;
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
 * @brief Draw a label for points and points sum in sidebar
 * @return Position of poins text
 */
SDL_Point Tetris::Ui::GameUi::writePoints()
{
    SDL_Point pos = {
        this->nextTileArea.x,
        (int)(this->nextTileArea.y + this->nextTileArea.w * 1.1)
    };

    this->writer->writeText("Punkty:", "Roboto", 48, pos, {255, 255, 255, 255}, this->nextTileArea.w * 0.8);

    pos.y *= 1.25;

    std::string points = this->formatPoints(this->player->getPoints());
    this->writer->writeText(points, "Telegrama", 48, pos, {16, 255, 16, 255}, this->nextTileArea.w);

    return pos;
}

/**
 * @brief Draw a label for level and current level in sidebar
 * @return Position of level text
 */
SDL_Point Tetris::Ui::GameUi::writeLevel(SDL_Point pointsLabelPosition)
{
    SDL_Point pos = {
        pointsLabelPosition.x,
        (int)(pointsLabelPosition.y * 1.2)
    };

    this->writer->writeText("Poziom:", "Roboto", 48, pos, {255, 255, 255, 255}, this->nextTileArea.w * 0.8);

    pos.y *= 1.15;

    std::string level = std::to_string(this->player->getLevel());
    this->writer->writeText(level, "Telegrama", 60, pos, {59, 131, 247, 255}, this->nextTileArea.w);

    return pos;
}

/**
 * @brief Get points formatted in 6 character format, with leading zeroes and maximum on 999999
 * @param points Sum of points
 * @return Formatted string
 */
std::string Tetris::Ui::GameUi::formatPoints(unsigned int points)
{
    std::string str = std::to_string(points);

    while (str.length() < 6) {
        str = '0' + str;
    }

    return str;
}
