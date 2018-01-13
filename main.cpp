#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "include/Config/config.h"
#include "include/utils.h"

using namespace std;

int main()
{
    SDL_Window* win = nullptr;
    SDL_Renderer* ren = nullptr;

    try {
        Config::Config::getInstance().load("config.ini");
    } catch (Config::ReadException &e) {
        cout << "Can't load config!" << endl;
    }

    if (! Utils::initSDL(win, ren)) {
        return 1;
    }

}
