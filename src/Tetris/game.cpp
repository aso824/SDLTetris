#include "include/Tetris/game.h"

/**
 * @brief Setter for Gfx::Engine
 * @param engine Shared pointer for Gfx::Engine instance
 */
void Tetris::Game::setGraphicsEngine(std::shared_ptr<Gfx::Engine> engine)
{
    this->engine = engine;
    this->ui = std::unique_ptr<Ui::GameUi>(new Ui::GameUi(this->engine, this->getMainGameRect()));
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

        this->ui->draw();
        this->engine->refresh();
    }
}

/**
 * @brief Calculate area for main game, depending of current window resolution
 * @return Area where main game should be drawed
 */
SDL_Rect Tetris::Game::getMainGameRect()
{
    float w = this->engine->getScreenWidth();
    float h = this->engine->getScreenHeight();

    SDL_Rect result;

    // Game UI ratio is 3:4
    if (w / h > 0.75) {
        result.w = h / 4 * 3;
        result.h = h;
        result.x = (w - result.w) / 2;
        result.y = 0;
    } else if (w / h == 0.75) {
        result.w = w;
        result.h = h;
        result.x = 0;
        result.y = 0;
    } else {
        result.w = w;
        result.h = w / 4 * 3;
        result.x = 0;
        result.y = (h - result.h) / 2;
    }

    return result;
}
