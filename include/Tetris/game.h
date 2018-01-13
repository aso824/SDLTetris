#ifndef GAME_H
#define GAME_H

#include <memory>
#include "include/Gfx/engine.h"

namespace Tetris {
    class Game
    {
        public:
            void setGraphicsEngine(std::shared_ptr<Gfx::Engine> engine);
            void start();

        protected:
            std::shared_ptr<Gfx::Engine> engine;

    };
}

#endif // GAME_H
