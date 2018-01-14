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
    static std::vector<std::string> explode(std::string const &s, char delimiter);

    template <typename T>
    static std::vector<std::vector<T>> transpose(std::vector<std::vector<T>> vec2d) {
        // Memory allocation
        std::vector<std::vector<T>> result(vec2d[0].size(), std::vector<T>(vec2d.size()));

        // Transposing
        for (unsigned int i = 0; i < vec2d[0].size(); i++) {
            for (unsigned int j = 0; j < vec2d.size(); j++) {
                result[i][j] = vec2d[j][i];
            }
        }

        return result;
    }
};

#endif // UTILS_H
