#include "include/Tetris/game.h"

/**
 * @brief Ctor
 */
Tetris::Game::Game()
{
    this->map = std::make_shared<Map>();

    // Prepare movement manager
    this->movementMgr = std::unique_ptr<MovementManager>(new MovementManager(this->map));
    this->movementMgr->addCollisionChecker(std::make_shared<Collisions::WallCollisionChecker>());
    this->movementMgr->addCollisionChecker(std::make_shared<Collisions::MapCollisionChecker>(this->map));

    this->currentTile = std::move(this->tileFactory.getRandomTileSharedPtr());
    this->nextTile = std::move(this->tileFactory.getRandomTileSharedPtr());

    this->player = std::make_shared<Player>();
}

/**
 * @brief Dtor
 */
Tetris::Game::~Game()
{

}

/**
 * @brief Setter for Gfx::Engine
 * @param engine Shared pointer for Gfx::Engine instance
 */
void Tetris::Game::setGraphicsEngine(std::shared_ptr<Gfx::Engine> engine)
{
    this->engine = engine;
    this->ui = std::unique_ptr<Ui::GameUi>(new Ui::GameUi(this->engine, this->getMainGameRect()));
    this->mapRen = std::make_shared<MapRenderer>(this->engine, this->map, this->ui->getTilesArea());

    this->ui->setPlayer(this->player);
}

/**
 * @brief Entry point for game
 */
void Tetris::Game::start()
{
    Logger::Logger::info("Game started");

    this->engine->clearScreen();
    this->ui->draw();
    this->ui->drawNextTile(this->nextTile);

    SDL_Event e;
    bool run = true;

    while(run) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                run = false;
            }

            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.scancode == SDL_SCANCODE_DOWN)
                    this->movementMgr->makeMove(this->currentTile, MOVE_DOWN);

                if (e.key.keysym.scancode == SDL_SCANCODE_LEFT)
                    this->movementMgr->makeMove(this->currentTile, MOVE_LEFT);

                if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT)
                    this->movementMgr->makeMove(this->currentTile, MOVE_RIGHT);

                if (e.key.keysym.scancode == SDL_SCANCODE_Z)
                    this->movementMgr->makeRotation(this->currentTile, ROTATE_LEFT);

                if (e.key.keysym.scancode == SDL_SCANCODE_X)
                    this->movementMgr->makeRotation(this->currentTile, ROTATE_RIGHT);
            }


        }

        this->mapRen->render();
        this->mapRen->drawTile(this->currentTile);

        // @TODO: repair bug with tile over frame and remove this fix
        this->ui->drawTilesFrame();

        if (!this->movementMgr->tick(this->currentTile)) {
            this->createNextTile();
        }

        this->map->deleteFullLines();

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

/**
 * @brief Push current tile into map, create next tile from factory
 */
void Tetris::Game::createNextTile()
{
    this->map->insertTile(this->currentTile);
    this->currentTile = this->nextTile;
    this->nextTile = std::move(this->tileFactory.getRandomTileSharedPtr());

    this->ui->drawNextTile(this->nextTile);
}
