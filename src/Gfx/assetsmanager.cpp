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
        if (std::get<2>(it) != nullptr) {
            // Free rect
            delete std::get<2>(it);
        }
    }

    for (auto &it: this->textureObjects) {
        if (it.second != nullptr) {
            SDL_DestroyTexture(it.second);
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
 * @brief Get asset from internal vector
 * @param assetName Name of asset to fetch
 * @return pair of texture and SDL_Rect for first SDL_RenderCopy parameter; both NULL if asset not found
 */
std::pair<SDL_Texture*, SDL_Rect*> Gfx::AssetsManager::getAsset(std::string assetName)
{
    std::pair<SDL_Texture*, SDL_Rect*> result;

    for (auto &it: *this->textures) {
        if (std::get<0>(it) == assetName) {
            result.first = std::get<1>(it);
            result.second = std::get<2>(it);
        }
    }

    return result;
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
        if (buf.empty())
            continue;

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
    std::string filename =manifestLine.at(2);
    SDL_Texture* tex = this->getTextureObject(filename);

    if (tex == nullptr) {
        Logger::Logger::warn("Failed to load texture: " + assetName);
        return false;
    }

    // Parse additional arguments
    SDL_Rect *rect = nullptr;
    if (manifestLine.size() == 7) {
        rect = new SDL_Rect;

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

/**
 * @brief Return SDL_Texture by name
 * @param filename Filename (key) with texture
 * @return SDL_Texture object
 */
SDL_Texture* Gfx::AssetsManager::getTextureObject(std::string &filename)
{
    if (this->textureObjects[filename] == nullptr) {
        std::string filepath = this->dir + "/images/" + filename;
        std::string extension = this->getFileExtension(filename);

        if (extension == "png") {
            this->textureObjects[filename] = IMG_LoadTexture(this->ren, filepath.c_str());
        } else {
            Logger::Logger::warn("Only PNG textures are currently supported, sorry!");
        }
    }

    return this->textureObjects.at(filename);
}
