#ifndef TILE_H
#define TILE_H

#include <vector>
#include <map>
#include <algorithm>
#include <SDL2/SDL.h>
#include "enums.h"
#include "include/utils.h"

namespace Tetris {
    typedef std::vector<std::vector<bool>> TileShape;

    class Tile
    {
        public:
            Tile(TileType type, SDL_Point pos);

            TileType getType();
            TileShape getShape();
            SDL_Rect getRect();
            unsigned short getWidth();
            unsigned short getHeight();
            SDL_Point getPosition();
            TileColors getColor();

            void setPosition(int x, int y);
            void setPosition(SDL_Point p);

            void rotateLeft();
            void rotateRight();
            void rotate(RotationDirection direction);

            void makeMove(MovementDirection direction);
        protected:
            TileType type;
            TileShape shape;
            TileColors color = TileColors::TILE_COLOR_BLANK;
            SDL_Rect rect;

            int angle = 0;
            int colorIndex = 0;

            void setColor();
            void setDimensions();
    };
}

#endif // TILE_H
