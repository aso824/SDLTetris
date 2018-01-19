#include "include/Tetris/map.h"

/**
 * @brief Ctor
 */
Tetris::Map::Map()
{
    // Allocate vector memory
    this->data = new MapData;

    for (int i = 0; i < 20; i++) {
        std::vector<TileColors> line(10);
        this->data->push_back(line);
    }
}

/**
 * @brief Dtor
 */
Tetris::Map::~Map()
{
    delete this->data;
}

/**
 * @brief Map data getter
 * @return MapData vector
 */
Tetris::Map::MapData*Tetris::Map::getData()
{
    return data;
}

/**
 * @brief Return color of block at given position
 * @param x Position in rows, without validation
 * @param y Position in columns, without validation
 * @return Block color at (X,Y)
 */
Tetris::TileColors Tetris::Map::getBlockAt(int x, int y)
{
    return this->data->at(y).at(x);
}

/**
 * @brief Set block at (X,Y) position to given color
 * @param x Position in rows, without validation
 * @param y Position in columns, without validation
 * @param color Color to be set
 */
void Tetris::Map::setBlockAt(int x, int y, Tetris::TileColors color)
{
    this->data->at(y).at(x) = color;
}

/**
 * @brief Insert tile into static map data
 * @param tile Tile object to insert, will not be affected
 */
void Tetris::Map::insertTile(std::shared_ptr<Tetris::Tile> tile)
{
    SDL_Rect dims = tile->getRect();
    TileShape shape = tile->getShape();
    TileColors color = tile->getColor();

    for (int x = 0; x < dims.w; x++) {
        for (int y = 0; y < dims.h; y++) {
            // Skip blank tile blocks
            if (shape[y][x] == TILE_COLOR_BLANK) {
                continue;
            }

            // Map tile block to map
            SDL_Point onMap = {
                dims.x + x,
                dims.y + y
            };

            // Skip blocks out of map range
            if (onMap.x < 0 || onMap.x > 9 || onMap.y < 0 || onMap.y > 19) {
                continue;
            }

            // Set block value on map
            this->setBlockAt(onMap.x, onMap.y, color);
        }
    }
}

/**
 * @brief Find full lines and return them
 * @return Vector with full lines indexes, counting like normal Y
 */
std::vector<int> Tetris::Map::findFullLines()
{
    std::vector<int> result;

    for (size_t y = 0; y < 20; y++) {
        bool currentLineFull = true;

        for (auto cell: this->data->at(y)) {
            if (cell == TILE_COLOR_BLANK) {
                currentLineFull = false;
                break;
            }
        }

        if (currentLineFull) {
            result.push_back(y);
        }
    }

    return result;
}

/**
 * @brief Delete given line from map
 * @param y Line index <0,19>, from up to down
 */
void Tetris::Map::deleteLine(int y)
{
    this->data->erase(this->data->begin() + y);
    this->data->insert(this->data->begin(), std::vector<TileColors>(10));
}

/**
 * @brief Delete multiple lines
 * @param lines Vector of lines index
 */
void Tetris::Map::deleteLines(std::vector<int> lines)
{
    for (auto &it: lines) {
        this->deleteLine(it);
    }
}

/**
 * @brief Find and delete all full lines
 * @return Count of deleted lines
 */
int Tetris::Map::deleteFullLines()
{
    std::vector<int> lines = this->findFullLines();
    this->deleteLines(lines);

    return lines.size();
}


