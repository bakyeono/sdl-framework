#ifndef C_IMAGE_H
#define C_IMAGE_H

#include "../lib.h"
#include "../common/CRect.h"

class CImage
{
public:
    explicit CImage(SDL_Surface* _surface);
    ~CImage();

public:
    inline SDL_Surface*  GetSurface();
    inline CRect         GetRect() const;

    inline void          Draw(SDL_Surface* dst_surface, CRect dst_rect);
    inline void          Draw(CRect src_rect,
                               SDL_Surface* dst_surface, CRect dst_rect);

private:
    SDL_Surface*         surface;
};

SDL_Surface* CImage::GetSurface()
{
    return surface;
}

CRect CImage::GetRect() const
{
    CRect rect(surface->w, surface->h, 0, 0);
    return rect;
}

void CImage::Draw(SDL_Surface* dst_surface, CRect dst_rect)
{
    SDL_BlitSurface(surface, 0, dst_surface, dst_rect.GetSDLRect());
}

void CImage::Draw(CRect src_rect, SDL_Surface* dst_surface, CRect dst_rect)
{
    SDL_BlitSurface(surface, src_rect.GetSDLRect(),
                    dst_surface, dst_rect.GetSDLRect());
}

#endif // C_IMAGE_H
