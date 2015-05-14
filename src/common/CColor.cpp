#include "./CColor.h"

CColor::CColor()
    : sdl_color( {0, 0, 0})
{
    screen_color = SDL_MapRGB(CScreenCtrl::Instance().GetSurface()->format,
                              sdl_color.r, sdl_color.g, sdl_color.b);
}

CColor::CColor(int red, int green, int blue)
{
    sdl_color.r = red;
    sdl_color.g = green;
    sdl_color.b = blue;
    screen_color = SDL_MapRGB(CScreenCtrl::Instance().GetSurface()->format,
                              sdl_color.r, sdl_color.g, sdl_color.b);
}

CColor::CColor(const SDL_Color& _sdl_color)
    : sdl_color(_sdl_color),
      screen_color(SDL_MapRGB(CScreenCtrl::Instance().GetSurface()->format,
                              sdl_color.r, sdl_color.g, sdl_color.b))
{
}

CColor::~CColor()
{
}
