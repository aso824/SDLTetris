#ifndef GAMEUI_H
#define GAMEUI_H

#include <memory>
#include "include/Gfx/engine.h"

namespace Tetris {
    namespace Ui {
        class GameUi
        {
            public:
                GameUi(std::shared_ptr<Gfx::Engine> engine, SDL_Rect area);
                void draw();

            protected:
                std::shared_ptr<Gfx::Engine> engine;
                SDL_Rect area;
        };
    }
}


#endif // GAMEUI_H