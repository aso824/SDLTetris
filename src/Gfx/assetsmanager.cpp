#include "include/Gfx/assetsmanager.h"

/**
 * @brief Ctor
 * @param assetsDirectory Directory with Manifest.txt and folders like "images" or "fonts"
 */
Gfx::AssetsManager::AssetsManager(std::shared_ptr<FontManager> fontmgr, std::string assetsDirectory) : dir(assetsDirectory)
{
    this->fontmgr = fontmgr;
}

/**
 * @brief Dtor
 */
Gfx::AssetsManager::~AssetsManager()
{

}

/**
 * @brief Load Manifest.txt and all files
 * @throws Exceptions::InvalidManifestException if file can't be opened or parsed
 */
void Gfx::AssetsManager::load()
{
    std::vector<std::vector<std::string> > manifest = this->loadManifest();
    Logger::Logger::ok("Manifest.txt from " + this->dir + " directory loaded");

    try {
        unsigned int count = 0;

        for (auto &it: manifest) {
            if (it.at(0) == "font") {
                this->loadFont(it);
                count++;
            }
        }

        Logger::Logger::ok("Loaded " + std::to_string(count) + " fonts");
    } catch (...) {
        throw Exceptions::InvalidManifestException();
    }
}

/**
 * @brief Load Manifest.txt from directory given in ctor
 * @return lines<vector<words>>, exploded by space
 * @throws Exceptions::InvalidManifestException if file can't be opened or parsed
 */
std::vector<std::vector<std::string> > Gfx::AssetsManager::loadManifest()
{
    std::vector<std::vector<std::string> > result;

    std::ifstream manifest(this->dir + "/Manifest.txt");

    if (! manifest.is_open()) {
        throw Exceptions::InvalidManifestException();
    }

    std::string buf;
    while (std::getline(manifest, buf)) {
        std::vector<std::string> line = Utils::explode(buf, ' ');
        result.push_back(line);
    }

    manifest.close();

    return result;
}

/**
 * @brief Gfx::AssetsManager::loadFont
 * @param manifestLine
 */
void Gfx::AssetsManager::loadFont(std::vector<std::string> manifestLine)
{
    this->fontmgr->addFont(manifestLine[1], this->dir + "/fonts/" + manifestLine[2]);
}
