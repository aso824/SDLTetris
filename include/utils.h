#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Utils
{
public:
    static bool initSDL(SDL_Window* win, SDL_Renderer* ren);
};

#endif // UTILS_H
