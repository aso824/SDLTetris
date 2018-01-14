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
 * @brief Clear screen with black color
 */
void Gfx::Engine::clearScreen()
{
    SDL_SetRenderDrawColor(this->ren, 0, 0, 0, 0);
    SDL_RenderClear(this->ren);
}

/**
 * @brief Calls SDL_RenderPresent
 */
void Gfx::Engine::refresh()
{
    SDL_RenderPresent(this->ren);
}

/**
 * @brief Draws a rectangle on renderer
 * @param rect Rectangle position and dimensions
 * @param color Line or fill color
 * @param filled If true, rectangle will be filled; otherwise only border will be drawn
 */
void Gfx::Engine::drawRect(SDL_Rect rect, SDL_Color* color, bool filled)
{
    if (color != nullptr) {
        SDL_SetRenderDrawColor(this->ren, color->r, color->g, color->b, color->a);
    }

    if (filled) {
        SDL_RenderFillRect(this->ren, &rect);
    } else {
        SDL_RenderDrawRect(this->ren, &rect);
    }
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

    if (TTF_Init() != 0) {
        throw Exceptions::SDLException("initializing TTF");
    }

    // Create window
    this->screenWidth = Config::Config::getInstance().getInt("screen_w", DEFAULT_SCREEN_W);
    this->screenHeight = Config::Config::getInstance().getInt("screen_h", DEFAULT_SCREEN_H);

    this->win = SDL_CreateWindow("SDL Tetris v1.0", 100, 100, this->screenWidth, this->screenHeight, SDL_WINDOW_SHOWN);

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

    // Create font manager
    this->fontmgr = std::make_shared<FontManager>();
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


