#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "include/Config/config.h"
#include "include/Logger/logger.h"
#include "include/utils.h"
#include "include/globals.h"

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

    return EXIT_SUCCESS;
}
