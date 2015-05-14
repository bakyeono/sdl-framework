#ifndef C_SCREEN_CTRL_H
#define C_SCREEN_CTRL_H

#include "../lib.h"
#include "../common/CRect.h"

using namespace std;

class CScreenCtrl
{
private:
    explicit CScreenCtrl();
    ~CScreenCtrl();
    CScreenCtrl(const CScreenCtrl&);
    const CScreenCtrl& operator = (const CScreenCtrl&);

public:
    inline static CScreenCtrl&   Instance();

public:
    inline void                  Refresh();
    inline SDL_Surface*          GetSurface();
    inline CRect                 GetRect() const;
    inline int                   GetWidth() const;
    inline int                   GetHeight() const;
    inline int                   GetBPP() const;
    inline void                  ClearBackground(Uint32 color) const;
    inline void                  Resize(int width, int height);

private:
    inline void                  Init();
    inline Uint32                MergeOptions();

private:
    SDL_Surface*          surface;
    int                   default_width;
    int                   default_height;
    int                   bpp;
    bool                  fullscreen;
    bool                  noframe;
    bool                  videomemory;
    bool                  resizeable;
};

CScreenCtrl& CScreenCtrl::Instance()
{
    static CScreenCtrl instance;
    return instance;
}

Uint32 CScreenCtrl::MergeOptions()
{
    Uint32 options;
    if (videomemory)
    {
        options = SDL_HWSURFACE;
    }
    else
    {
        options = SDL_SWSURFACE;
    }
    if (fullscreen)
    {
        options = options | SDL_FULLSCREEN;
    }
    if (noframe)
    {
        options = options | SDL_NOFRAME;
    }
    if (resizeable)
    {
        options = options | SDL_RESIZABLE;
    }
    return options;
}

void CScreenCtrl::Init()
{
    surface = SDL_SetVideoMode(default_width, default_height, bpp,
                               MergeOptions());
}

SDL_Surface* CScreenCtrl::GetSurface()
{
    return surface;
}

CRect CScreenCtrl::GetRect() const
{
    return CRect(surface->w, surface->h, 0, 0);
}

void CScreenCtrl::Refresh()
{
    SDL_Flip(surface);
}

int CScreenCtrl::GetWidth() const
{
    return surface->w;
}

int CScreenCtrl::GetHeight() const
{
    return surface->h;
}

int CScreenCtrl::GetBPP() const
{
    return bpp;
}

void CScreenCtrl::ClearBackground(Uint32 color) const
{
    SDL_FillRect(surface, 0, color);
}

void CScreenCtrl::Resize(int width, int height)
{
    surface = SDL_SetVideoMode(width, height, bpp, MergeOptions());
}

#endif // C_SCREEN_CTRL_H
