#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>
#include <sstream>

class Utils
{
public:
    static bool initSDL(SDL_Window* win, SDL_Renderer* ren);
    static std::vector<std::string> explode(std::string const &s, char delimiter);
};

#endif // UTILS_H
