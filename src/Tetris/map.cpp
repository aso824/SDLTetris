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


