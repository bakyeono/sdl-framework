#ifndef C_COLOR_H
#define C_COLOR_H

#include "../lib.h"
#include "../ctrl/CScreenCtrl.h"

class CColor
{
public:
    explicit CColor();
    explicit CColor(int red, int green, int blue);
    explicit CColor(const SDL_Color& _sdl_color);
    ~CColor();

public:
    inline SDL_Color GetSDLColor() const;
    inline void      SetSDLColor(const SDL_Color& _sdl_color);
    inline void      SetSDLColor(int red, int green, int blue);
    inline Uint32    GetScreenColor() const;

private:
    SDL_Color sdl_color;
    Uint32    screen_color;
};

SDL_Color CColor::GetSDLColor() const
{
    return sdl_color;
}

void CColor::SetSDLColor(int red, int green, int blue)
{
    sdl_color.r = red;
    sdl_color.g = green;
    sdl_color.b = blue;
    screen_color = SDL_MapRGB(CScreenCtrl::Instance().GetSurface()->format,
                              sdl_color.r, sdl_color.g, sdl_color.b);
}

void CColor::SetSDLColor(const SDL_Color& _sdl_color)
{
    sdl_color = _sdl_color;
    screen_color = SDL_MapRGB(CScreenCtrl::Instance().GetSurface()->format,
                              sdl_color.r, sdl_color.g, sdl_color.b);
}

Uint32 CColor::GetScreenColor() const
{
    return screen_color;
}

#endif // C_COLOR_H
