#include "include/Gfx/engine.h"

/**
 * @brief Ctor
 */
Gfx::Engine::Engine()
{
    this->initAll();
}

/**
 * @brief Dtor
 */
Gfx::Engine::~Engine()
{
    this->destroyAll();
}

/**
 * @brief Calls destroy and init to reinitialize SDL and it subsystems
 */
void Gfx::Engine::restart()
{
    this->destroyAll();
    this->initAll();
}

/**
 * @brief Initialize SDL and subsystems, create objects like window and renderer
 */
void Gfx::Engine::initAll()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        throw Exceptions::SDLException("initializing SDL");
    }

    const int w = Config::Config::getInstance().getInt("screen_w", DEFAULT_SCREEN_W);
    const int h = Config::Config::getInstance().getInt("screen_h", DEFAULT_SCREEN_H);

    this->win = SDL_CreateWindow("SDL Tetris v1.0", 100, 100, w, h, SDL_WINDOW_SHOWN);

    if (this->win == nullptr) {
        throw Exceptions::SDLException("creating window");
    }

}

/**
 * @brief Destroy objects like window and renderer, quit SDL and subsystems
 */
void Gfx::Engine::destroyAll()
{
    SDL_DestroyWindow(this->win);
    SDL_Quit();
}


