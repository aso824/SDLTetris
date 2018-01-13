#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "include/Config/config.h"
#include "include/Logger/logger.h"
#include "include/utils.h"

using namespace std;

int main()
{
    Logger::Logger::info("SDLTetris v1.0");

    SDL_Window* win = nullptr;
    SDL_Renderer* ren = nullptr;

    try {
        Config::Config::getInstance().load("config.ini");
    } catch (Config::ReadException &e) {
        Logger::Logger::warn(e.what());

        try {
            Config::Config::getInstance().createNew();
            Config::Config::getInstance().load("config.ini");
        } catch (...) {
            Logger::Logger::error("Could not create new config file!");
            return 1;
        }
    }

    if (! Utils::initSDL(win, ren)) {
        return 1;
    }

}
