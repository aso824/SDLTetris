#include <iostream>
#include <memory>

#include "include/globals.h"
#include "include/Config/config.h"
#include "include/Logger/logger.h"
#include "include/Gfx/engine.h"
#include "include/Tetris/game.h"

using namespace std;

int main()
{
    Logger::Logger::info("SDLTetris v1.0");

    // Set some settings from globals
    Config::Config::getInstance().setPath(Globals::configFilename);

    // Config loading
    try {
        Config::Config::getInstance().load();
    } catch (Config::ReadException &e) {
        Logger::Logger::warn(e.what());

        try {
            Config::Config::getInstance().createNew();
        } catch (...) {
            Logger::Logger::error("Could not create new config file!");

            return EXIT_FAILURE;
        }
    }

    // Graphics engine initialization
    shared_ptr<Gfx::Engine> engine;

    try {
        engine = shared_ptr<Gfx::Engine>(new Gfx::Engine());
    } catch (Gfx::Exceptions::SDLException &e) {
        Logger::Logger::error(e.what());

        return EXIT_FAILURE;
    }

    // Tetris game main object
    unique_ptr<Tetris::Game> game;

    try {
        game = unique_ptr<Tetris::Game>(new Tetris::Game());

        game->setGraphicsEngine(engine);

        game->start();
    } catch (...) {
        Logger::Logger::error("Unhandled Tetris::Game exception in main()");

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
