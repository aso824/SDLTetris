#include "include/utils.h"

/**
 * @brief Simple equivalent of PHP's explode() method
 * @param s String to be exploded
 * @param delimiter Characted to use for separation
 * @return Vector of string elements after explode
 */
std::vector<std::string> Utils::explode(const std::string& s, char delimiter)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delimiter); ) {
        result.push_back(std::move(token));
    }

    return result;
}

