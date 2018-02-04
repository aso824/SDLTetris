#ifndef BLOCKDRAWER_H
#define BLOCKDRAWER_H

#include <memory>
#include <string>
#include "include/Tetris/enums.h"
#include "include/Gfx/engine.h"

namespace Tetris {
    class BlockDrawer
    {
        public:
            BlockDrawer(std::shared_ptr<Gfx::Engine> engine);

            void setBlockSize(float size);
            float getBlockSize();

            void setArea(SDL_Rect area, unsigned short rows, unsigned short columns);

            void drawBlock(TileColors color, SDL_Point p);
            void drawBlock(TileColors color, unsigned short x, unsigned short y);

        protected:
            std::shared_ptr<Gfx::Engine> engine;
            float blockSize = 0;
            SDL_Rect area;
            unsigned short rows = 0, columns = 0;

    };
}

#endif // BLOCKDRAWER_H
