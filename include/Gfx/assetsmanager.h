#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include <tuple>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "fontmanager.h"
#include "Exceptions/invalidmanifestexception.h"
#include "include/utils.h"
#include "include/Logger/logger.h"

namespace Gfx {
    class AssetsManager
    {
        public:
            AssetsManager(SDL_Renderer* ren, std::shared_ptr<FontManager> fontmgr, std::string assetsDirectory = "assets");
            ~AssetsManager();

            void load();
            std::pair<SDL_Texture*, SDL_Rect*> getAsset(std::string assetName);

        protected:
            std::string dir;
            SDL_Renderer* ren;
            std::shared_ptr<FontManager> fontmgr;
            std::unique_ptr<std::vector<std::tuple<std::string, SDL_Texture*, SDL_Rect*>>> textures;

            std::vector<std::vector<std::string>> loadManifest();
            void loadFont(std::vector<std::string> manifestLine);
            bool loadTexture(std::vector<std::string> manifestLine);
            std::string getFileExtension(std::string filename);
    };
}

#endif // ASSETSMANAGER_H
