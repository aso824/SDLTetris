#include "include/Gfx/textwriter.h"

/**
 * @brief Ctor
 * @param engine Initialized Gfx::Engine
 */
Gfx::TextWriter::TextWriter(const std::shared_ptr<Engine>& engine)
{
    this->engine = engine;
    this->fontmgr = engine->getFontManager();
}

/**
 * @brief Write text on screen, using given font, on given point, with downscaled width
 * @param s String to be written
 * @param f Gfx::Font with TTF_Font* loaded
 * @param pos Text position, point is on upper-left corner
 * @param color Text color
 * @param width Autoscale to given width, give 0 to disable
 * @param centered Give width as desired area.w, pos.x for area.x and text will be centered
 */
void Gfx::TextWriter::writeText(std::string s, Gfx::Font f, SDL_Point pos, SDL_Color color, int width, bool centered)
{
    SDL_Surface *surf = TTF_RenderUTF8_Blended(f.fontObj, s.c_str(), color);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(this->engine->getRenderer(), surf);
    SDL_FreeSurface(surf);

    SDL_Rect r = {pos.x, pos.y, 0, 0};

    // Only downscalling
    int w = 0;
    SDL_QueryTexture(tex, NULL, NULL, &w, NULL);

    if (w > width) {
        r.w = width;
    }

    if (centered) {
        r.x = pos.x + width / 2 - w / 2;
    }

    this->engine->renderTexture(tex, r);
    SDL_DestroyTexture(tex);
}

/**
 * @brief Alias for writeText(string, Font, SDL_Point, width) with automatic font lookup
 * @param s String to be written
 * @param fontName Font name, must be loaded into FontManager
 * @param size Font size
 * @param pos Text position, point is on upper-left corner
 * @param color Text color
 * @param width Autoscale to given width, give 0 to disable
 * @param centered Give width as desired area.w, pos.x for area.x and text will be centered
 */
void Gfx::TextWriter::writeText(std::string s, std::string fontName, int size, SDL_Point pos, SDL_Color color, int width, bool centered)
{
    Font f = this->fontmgr->getFont(fontName, size);
    this->writeText(s, f, pos, color, width, centered);
}
