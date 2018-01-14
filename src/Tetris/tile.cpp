#include "include/Tetris/tile.h"

/**
 * @brief Ctor
 * @param type Type of tile form enums.h
 */
Tetris::Tile::Tile(TileType type, SDL_Point pos) : type(type)
{
    // Static data with all tile shapes
    static const bool shapeData[7][4][4] = {
        // I
        {{1}, {1}, {1}, {1}},
        // T
        {{1, 1, 1}, {0, 1, 0}},
        // O
        {{1, 1}, {1, 1}},
        // L
        {{1, 0}, {1, 0}, {1, 1}},
        // J
        {{0, 1}, {0, 1}, {1, 1}},
        // S
        {{0, 1, 1}, {1, 1, 0}},
        // Z
        {{1, 1, 0}, {0, 1, 1}}
    };

    // Call some internal setters
    this->setDimensions();
    this->setColor();
    this->setPosition(pos);

    // Copy shape from static data to internal vector
    for (int i = 0; i < this->getHeight(); i++) {
        std::vector<bool> row;

        for (int j = 0; j < this->getWidth(); j++)
            row.push_back(shapeData[type][i][j]);

        this->shape.push_back(row);
    }
}

/**
 * @brief Get tile type
 * @return Tile type
 */
Tetris::TileType Tetris::Tile::getType()
{
    return this->type;
}

/**
 * @brief Get tile shape vector
 * @return Tile shape vector
 */
Tetris::TileShape Tetris::Tile::getShape()
{
    return this->shape;
}

/**
 * @brief Get tile rect
 * @return SDL_Rect - position and dimensions
 */
SDL_Rect Tetris::Tile::getRect()
{
    return this->rect;
}

/**
 * @brief Get tile width
 * @return Tile width from SDL_Rect object
 */
unsigned short Tetris::Tile::getWidth()
{
    return this->rect.w;
}

/**
 * @brief Get tile height
 * @return Tile height from SDL_Rect object
 */
unsigned short Tetris::Tile::getHeight()
{
    return this->rect.h;
}

/**
 * @brief Get tile position on map
 * @return SDL_Point position extracted from SDL_Rect
 */
SDL_Point Tetris::Tile::getPosition()
{
    return {
        this->rect.x,
        this->rect.y
    };
}

/**
 * @brief Get color associated with current tile type
 * @return Color from enums.h
 */
Tetris::TileColors Tetris::Tile::getColor()
{
    return this->color;
}

/**
 * @brief Set tile positon in map
 * @param x Position in X axis
 * @param y Position in Y axis
 */
void Tetris::Tile::setPosition(int x, int y)
{
    this->rect.x = x;
    this->rect.y = y;
}

/**
 * @brief Set tile position in map
 * @param p SDL_Point with (x,y) position
 */
void Tetris::Tile::setPosition(SDL_Point p)
{
    this->setPosition(p.x, p.y);
}

/**
 * @brief Set tile color, depends of tile type
 */
void Tetris::Tile::setColor()
{
    switch (type) {
        case I: this->color = TILE_COLOR_CYAN; break;
        case J: this->color = TILE_COLOR_BLUE; break;
        case L: this->color = TILE_COLOR_ORANGE; break;
        case O: this->color = TILE_COLOR_ORANGE; break;
        case S: this->color = TILE_COLOR_GREEN; break;
        case T: this->color = TILE_COLOR_PURPLE; break;
        case Z: this->color = TILE_COLOR_RED; break;
    }
}

/**
 * @brief Set tile dimensions, depends of tile type
 */
void Tetris::Tile::setDimensions()
{
    unsigned short w, h;

    switch (this->type) {
        case I: w = 1; h = 4; break;
        case T: w = 3; h = 2; break;
        case O: w = 2; h = 2; break;
        case L:
        case J: w = 2; h = 3; break;
        case S:
        case Z: w = 3; h = 2; break;
    }

    this->rect.w = w;
    this->rect.h = h;
}


