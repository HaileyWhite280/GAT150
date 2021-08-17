#include "Font.h"

nc::Font::~Font()
{
    if (font != nullptr)
    {
        TTF_CloseFont(font);
    }
}

bool nc::Font::Load(const std::string& name, void* data)
{
    font = TTF_OpenFont(name.c_str(), (int)data); //deref pixel size

    if (font == nullptr)
    {
        std::cout << "TTF_OpenFont Error:" << TTF_GetError() << std::endl;
        return false;
    }

    return true;
}

SDL_Surface* nc::Font::CreateSurface(const std::string& text, const nc::Color& color)
{
    /*SDL_Surface* surface = TTF_RenderText_Solid(TTF_Font, text, color);

    if (surface == nullptr)
    {
        std::cout << "TTF_RenderText_Solid Error:" << SDL_GetError() << std::endl;
    }
    return surface;*/
}
