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
 * @brief Clear area by drawing a recangle in desired color, or black by default
 * @param rect Rect to be cleared
 * @param color Color for clearing, default black
 */
void Gfx::Engine::clearRect(SDL_Rect rect, SDL_Color color)
{
    this->drawRect(rect, &color, true);
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
 * @brief Render given texture at screen
 * @param tex Texture to be rendered
 * @param position Texture position and dimensions, W and H will be filled with aspect ratio
 */
void Gfx::Engine::renderTexture(SDL_Texture* tex, SDL_Rect pos)
{
    int w = 0, h = 0;
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);

    // Autoscalling feature
    if (pos.w == 0 || pos.h == 0) {
        if (pos.w == 0 && pos.h == 0) {
            // Both W and H empty, draw in original size
            pos.w = w;
            pos.h = h;
        } else {
            // Only width or height is empty, need to scale with aspect ratio
            if (pos.w == 0) {
                // Calculate width, depends on height
                pos.w = (int)((float)pos.h / (float)h * (float)w);
            } else {
                // Calculate height, depends on width
                pos.h = (int)((float)pos.w / (float)w * (float)h);
            }
        }
    }

    SDL_RenderCopy(this->ren, tex, NULL, &pos);
}

/**
 * @brief Alias for renderTexture(tex, rect)
 * @param tex Texture to be rendered
 * @param pos Where texture will be rendered
 */
void Gfx::Engine::renderTexture(SDL_Texture* tex, SDL_Point pos)
{
    this->renderTexture(tex, {pos.x, pos.y, 0, 0});
}

/**
 * @brief Render asset on desired place
 * @param assetName Asset loaded by AssetsManager internal instance
 * @param pos Wherwe texture will be rendered
 */
void Gfx::Engine::renderTexture(std::string assetName, SDL_Point pos)
{
    std::pair<SDL_Texture*, SDL_Rect*> asset = this->assets->getAsset(assetName);

    if (asset.first == nullptr) {
        Logger::Logger::warn("Can't render texture, unknown asset: " + assetName);
        return;
    }

    SDL_Rect dst = {
        pos.x,
        pos.y,
        0, 0
    };

    SDL_Rect* src = nullptr;

    if (asset.second != nullptr) {
        src = asset.second;

        dst.w = src->w;
        dst.h = src->h;
    } else {
        SDL_QueryTexture(asset.first, NULL, NULL, &dst.w, &dst.h);
    }

    SDL_RenderCopy(this->ren, asset.first, src, &dst);
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

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        throw Exceptions::SDLException("initializing IMG");
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

    // Create assets manager and load files
    this->assets = std::make_shared<AssetsManager>(this->ren, this->fontmgr, "assets");
    this->assets->load();
}

/**
 * @brief Destroy objects like window and renderer, quit SDL and subsystems
 */
void Gfx::Engine::destroyAll()
{
    SDL_DestroyRenderer(this->ren);
    SDL_DestroyWindow(this->win);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


