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

            void setBlockSize(unsigned short size);
            unsigned short getBlockSize();
            void drawBlock(TileColors color, SDL_Point p);

        protected:
            std::shared_ptr<Gfx::Engine> engine;
            unsigned short blockSize = 0;
    };
}

#endif // BLOCKDRAWER_H
