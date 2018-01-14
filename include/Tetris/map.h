#ifndef MAP_H
#define MAP_H

#include <vector>
#include "enums.h"

namespace Tetris {
    class Map
    {
        typedef std::vector<std::vector<TileColors>> MapData;

        public:
            Map();
            ~Map();

            MapData* getData();

        protected:
            MapData* data;
    };
}

#endif // MAP_H
