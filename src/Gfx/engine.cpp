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
    // Init SDL and subsystems
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        throw Exceptions::SDLException("initializing SDL");
    }

    // Create window
    const int w = Config::Config::getInstance().getInt("screen_w", DEFAULT_SCREEN_W);
    const int h = Config::Config::getInstance().getInt("screen_h", DEFAULT_SCREEN_H);

    this->win = SDL_CreateWindow("SDL Tetris v1.0", 100, 100, w, h, SDL_WINDOW_SHOWN);

    if (this->win == nullptr) {
        throw Exceptions::SDLException("creating window");
    }

    // Create renderer
    unsigned int rendererFlags = 0;

    if (Config::Config::getInstance().getBoolean("vsync", DEFAULT_VSYNC)) {
        rendererFlags |= SDL_RENDERER_PRESENTVSYNC;
    }

    if (Config::Config::getInstance().getBoolean("ren_software", DEFAULT_RENDERER_SOFTWARE) == true) {
        rendererFlags |= SDL_RENDERER_SOFTWARE;
    } else {
        rendererFlags |= SDL_RENDERER_ACCELERATED;
    }

    this->ren = SDL_CreateRenderer(this->win, -1, rendererFlags);

    if (this->ren == nullptr) {
        throw Exceptions::SDLException("creating renderer");
    }

}

/**
 * @brief Destroy objects like window and renderer, quit SDL and subsystems
 */
void Gfx::Engine::destroyAll()
{
    SDL_DestroyRenderer(this->ren);
    SDL_DestroyWindow(this->win);
    SDL_Quit();
}


