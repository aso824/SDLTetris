#include "include/Tetris/game.h"

/**
 * @brief Setter for Gfx::Engine
 * @param engine Shared pointer for Gfx::Engine instance
 */
void Tetris::Game::setGraphicsEngine(std::shared_ptr<Gfx::Engine> engine)
{
    this->engine = engine;
}

/**
 * @brief Entry point for game
 */
void Tetris::Game::start()
{
    this->engine->clearScreen();

    SDL_Event e;
    bool run = true;

    while(run) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                run = false;
            }
        }

        this->engine->refresh();
    }
}
