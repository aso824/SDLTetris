#include "include/Gfx/assetsmanager.h"

/**
 * @brief Ctor
 * @param assetsDirectory Directory with Manifest.txt and folders like "images" or "fonts"
 */
Gfx::AssetsManager::AssetsManager(SDL_Renderer* ren, std::shared_ptr<FontManager> fontmgr, std::string assetsDirectory) : dir(assetsDirectory)
{
    this->ren = ren;
    this->fontmgr = fontmgr;
    this->textures = std::unique_ptr<std::vector<std::tuple<std::string, SDL_Texture*, SDL_Rect*>>>(
                new std::vector<std::tuple<std::string, SDL_Texture*, SDL_Rect*>>
    );
}

/**
 * @brief Dtor
 */
Gfx::AssetsManager::~AssetsManager()
{
    for (auto &it: *this->textures) {
        if (std::get<1>(it) != nullptr) {
            SDL_DestroyTexture(std::get<1>(it));
        }
    }
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
        unsigned int fontsCount = 0,
                     texturesCount = 0;

        for (auto &it: manifest) {
            if (it.at(0) == "font") {
                this->loadFont(it);
                fontsCount++;
            } else if (it.at(0) == "texture") {
                if (this->loadTexture(it)) {
                    texturesCount++;
                }
            } else {
                Logger::Logger::warn("Unknown asset type: " + it.at(0));
            }
        }

        Logger::Logger::ok("Loaded " + std::to_string(fontsCount) + " fonts");
        Logger::Logger::ok("Loaded " + std::to_string(texturesCount) + " textures");
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
 * @brief Load font from Manifest.txt line into FontManager instance
 * @param manifestLine Vector of words, exploded by spaces
 */
void Gfx::AssetsManager::loadFont(std::vector<std::string> manifestLine)
{
    this->fontmgr->addFont(manifestLine[1], this->dir + "/fonts/" + manifestLine[2]);
}

/**
 * @brief Load texture from Manifest.txt line into internal memory
 * @param manifestLine Vector of words, exploded by spaces
 */
bool Gfx::AssetsManager::loadTexture(std::vector<std::string> manifestLine)
{
    std::string assetName = manifestLine.at(1);
    std::string filepath = this->dir + "/images/" + manifestLine.at(2);
    std::string extension = this->getFileExtension(manifestLine.at(2));
    SDL_Texture* tex = nullptr;

    if (extension == "png") {
        tex = IMG_LoadTexture(this->ren, filepath.c_str());
    } else {
        Logger::Logger::warn("Only PNG textures are currently supported, sorry!");
        return false;
    }

    if (tex == nullptr) {
        Logger::Logger::warn("Failed to load texture: " + assetName);
        return false;
    }

    // Parse additional arguments
    SDL_Rect *rect = nullptr;
    if (manifestLine.size() == 7) {
        rect->x = stoi(manifestLine.at(3));
        rect->y = stoi(manifestLine.at(4));
        rect->w = stoi(manifestLine.at(5));
        rect->h = stoi(manifestLine.at(6));
    }

    std::tuple<std::string, SDL_Texture*, SDL_Rect*> result(assetName, tex, rect);
    this->textures->push_back(result);

    return true;
}

/**
 * @brief Extract file extension from file name
 * @param filename File name to process
 * @return File extension
 */
std::string Gfx::AssetsManager::getFileExtension(std::string filename)
{
    std::vector<std::string> parts = Utils::explode(filename, '.');
    return parts.back();
}
