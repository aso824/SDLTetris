#include "include/utils.h"

/**
 * @brief Init SDL with extensions, create window and renderer
 * @param win Empty pointer for window
 * @param ren Empty pointer for renderer
 * @return True is everything is up
 */
bool Utils::initSDL(SDL_Window *win, SDL_Renderer *ren)
{
    return true;
}

std::vector<std::string> Utils::explode(const std::string& s, char delimiter)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delimiter); ) {
        result.push_back(std::move(token));
    }

    return result;
}

