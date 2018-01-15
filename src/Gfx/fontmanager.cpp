#include "include/Gfx/fontmanager.h"

/**
 * @brief Ctor
 */
Gfx::FontManager::FontManager()
{
    this->fontFiles = std::unique_ptr<std::map<std::string, std::string>>(new std::map<std::string, std::string>);
    this->fonts = std::unique_ptr<std::vector<Font>>(new std::vector<Font>);
}

/**
 * @brief Dtor
 */
Gfx::FontManager::~FontManager()
{
    this->clearCache();
}

/**
 * @brief Add font to dictionary
 * @param fontName Name of font in manager
 * @param filename Filename inside /assets/fonts directory, with extension
 */
void Gfx::FontManager::addFont(std::string fontName, std::string filename)
{
    this->fontFiles->at(fontName) = filename;
}

/**
 * @brief Return font in desired size from cache or reload
 * @param fontName Name of font in manager
 * @param size Desired size
 * @return Font structure with TTF_Font* inside
 * @throws UnknownFontException when trying to load font that isn't in dictionary
 */
Gfx::Font Gfx::FontManager::getFont(std::string fontName, int size)
{
    // Unknown font name
    if (! this->isFontExistInDictionary(fontName)) {
        throw Exceptions::UnknownFontException(fontName);
    }

    for (auto &it: *this->fonts) {
        if (it.name == fontName && it.size == size) {
            // Cache hit
            return it;
        }
    }

    // Cache miss
    return this->loadFont(fontName, size);
}

/**
 * @brief Delete all fonts and free memory
 */
void Gfx::FontManager::clearCache()
{
    for (int i = this->fonts->size() - 1; i >= 0; i--) {
        TTF_CloseFont(this->fonts->at(i).fontObj);
        this->fonts->erase(this->fonts->begin() + i);
    }
}

/**
 * @brief Search fontName in fontFiles map
 * @param fontName Name to be searched
 * @return True if font exists in fontFiles map, false otherwise
 */
bool Gfx::FontManager::isFontExistInDictionary(std::string fontName)
{
    std::map<std::string, std::string>::const_iterator it;
    it = this->fontFiles->find(fontName);

    return (it != this->fontFiles->end());
}

/**
 * @brief Load font in desired size and add it to internal cache
 * @param fontName Font name, must be added by addFont function
 * @param size Font size to be loaded
 * @return Gfx::Font structure
 */
Gfx::Font Gfx::FontManager::loadFont(std::string fontName, int size)
{
    Gfx::Font newFont;
    newFont.name = fontName;
    newFont.size = size;

    std::string filepath = this->fontFiles->at(fontName);
    newFont.fontObj = TTF_OpenFont(filepath.c_str(), size);

    this->fonts->push_back(newFont);
    return newFont;
}
