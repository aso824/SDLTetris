#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H

#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include "fontmanager.h"
#include "Exceptions/invalidmanifestexception.h"
#include "include/utils.h"
#include "include/Logger/logger.h"

namespace Gfx {
    class AssetsManager
    {
        public:
            AssetsManager(std::shared_ptr<FontManager> fontmgr, std::string assetsDirectory = "assets");
            ~AssetsManager();

            void load();

        protected:
            std::string dir;
            std::shared_ptr<FontManager> fontmgr;

            std::vector<std::vector<std::string>> loadManifest();
            void loadFont(std::vector<std::string> manifestLine);
    };
}

#endif // ASSETSMANAGER_H
