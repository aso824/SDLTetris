#ifndef MAP_H
#define MAP_H

#include <memory>
#include <vector>
#include "enums.h"
#include "tile.h"

namespace Tetris {
    class Map
    {
        typedef std::vector<std::vector<TileColors>> MapData;

        public:
            Map();
            ~Map();

            MapData* getData();

            TileColors getBlockAt(int x, int y);
            void setBlockAt(int x, int y, TileColors color);

            void insertTile(std::shared_ptr<Tile> tile);

            int deleteFullLines();

        protected:
            MapData* data;

            std::vector<int> findFullLines();
            void deleteLine(int y);
            void deleteLines(std::vector<int> lines);
    };
}

#endif // MAP_H
