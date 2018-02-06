#include "include/Tetris/Ui/sidebarplayerinfo.h"

/**
 * @brief Ctor
 * @param engine Graphics engine, already initialized
 * @param nextTileArea Area for nextTile, required for positioning elements in this class
 */
Tetris::Ui::SidebarPlayerInfo::SidebarPlayerInfo(std::shared_ptr<Gfx::Engine> engine, SDL_Rect nextTileArea)
    : engine(engine), nextTileArea(nextTileArea)
{
    this->calculatePositions();
}

/**
 * @brief Redraw all labels and values in sidebar
 * @param player Player instance
 */
void Tetris::Ui::SidebarPlayerInfo::updateData(std::shared_ptr<Tetris::Player> player)
{
    this->points = player->getPoints();
    this->level = player->getLevel();

    this->clearInfoArea();
    this->drawLabels();

    this->drawPointsLabel();
    this->drawLevelLabel();
}

/**
 * @brief Set internal SDL_Point's - calculate position for all texts
 */
void Tetris::Ui::SidebarPlayerInfo::calculatePositions()
{

}

/**
 * @brief Clear whole area handled by this class
 */
void Tetris::Ui::SidebarPlayerInfo::clearInfoArea()
{

}

/**
 * @brief Draw labels for points and level in sidebar
 */
void Tetris::Ui::SidebarPlayerInfo::drawLabels()
{
    this->clearInfoArea();

    this->drawPointsLabel();
    this->drawLevelLabel();
}

/**
 * @brief Draw label for points
 */
void Tetris::Ui::SidebarPlayerInfo::drawPointsLabel()
{

}

/**
 * @brief Draw label for level
 */
void Tetris::Ui::SidebarPlayerInfo::drawLevelLabel()
{

}

/**
 * @brief Draw points value
 */
void Tetris::Ui::SidebarPlayerInfo::drawPointsValue()
{

}

/**
 * @brief Draw points value
 */
void Tetris::Ui::SidebarPlayerInfo::drawLevelValue()
{

}

