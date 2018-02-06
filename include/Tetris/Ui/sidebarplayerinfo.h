#ifndef SIDEBARPLAYERINFO_H
#define SIDEBARPLAYERINFO_H

#include <memory>
#include <SDL2/SDL.h>
#include "include/Tetris/player.h"
#include "include/Gfx/engine.h"

namespace Tetris {
    namespace Ui {
        class SidebarPlayerInfo
        {
            public:
                SidebarPlayerInfo(std::shared_ptr<Gfx::Engine> engine, SDL_Rect nextTileArea);

                void updateData(std::shared_ptr<Player> player);

            protected:
                std::shared_ptr<Gfx::Engine> engine;
                SDL_Rect nextTileArea;
                SDL_Point playerPoints,
                    playerPointsLabel,
                    playerLevel,
                    playerLevelLabel;

                unsigned int points = 0;
                unsigned int level = 1;

                void calculatePositions();
                void clearInfoArea();

                void drawLabels();

                void drawPointsLabel();
                void drawLevelLabel();

                void drawPointsValue();
                void drawLevelValue();
        };
    }
}

#endif // SIDEBARPLAYERINFO_H
