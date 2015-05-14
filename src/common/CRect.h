#ifndef C_RECT_H
#define C_RECT_H

#include "../lib.h"
#include "./CPos.h"

class CRect
{
public:
    inline explicit CRect();
    inline explicit CRect(SDL_Rect _sdl_rect);
    inline explicit CRect(int width, int height, const CPos& pos);
    inline explicit CRect(int width, int height, int x, int y);
    inline ~CRect();

public:
    inline int          GetWidth() const;
    inline int          GetHeight() const;
    inline CPos         GetPos() const;
    inline int          GetPosX() const;
    inline int          GetPosY() const;
    inline void         SetWidth(int width);
    inline void         SetHeight(int height);
    inline void         SetPosX(int x);
    inline void         SetPosY(int y);
    inline void         SetPos(int x, int y);
    inline void         SetPos(const CPos& pos);
    inline void         SetSDLRect(SDL_Rect _sdl_rect);
    inline SDL_Rect*    GetSDLRect();
    inline CRect        CalcOffset(const CPos& pos) const;
    inline CRect        CalcOffset(const CRect& rect) const;
    inline bool         HasPos(CPos pos);

private:
    SDL_Rect     sdl_rect;
};

CRect::CRect()
    : sdl_rect({0, 0, 0, 0})
{
}

CRect::CRect(SDL_Rect _sdl_rect)
    : sdl_rect(_sdl_rect)
{
}

CRect::CRect(int width, int height, const CPos& pos)
{
    sdl_rect.w = width;
    sdl_rect.h = height;
    sdl_rect.x = pos.GetX();
    sdl_rect.y = pos.GetY();
}

CRect::CRect(int width, int height, int x, int y)
{
    sdl_rect.w = width;
    sdl_rect.h = height;
    sdl_rect.x = x;
    sdl_rect.y = y;
}

CRect::~CRect()
{
}

int CRect::GetWidth() const
{
    return sdl_rect.w;
}

int CRect::GetHeight() const
{
    return sdl_rect.h;
}

int CRect::GetPosX() const
{
    return sdl_rect.x;
}

int CRect::GetPosY() const
{
    return sdl_rect.y;
}

CPos CRect::GetPos() const
{
    return CPos(sdl_rect.x, sdl_rect.y);
}

SDL_Rect* CRect::GetSDLRect()
{
    return &sdl_rect;
}

void CRect::SetWidth(int width)
{
    sdl_rect.w = width;
}

void CRect::SetHeight(int height)
{
    sdl_rect.h = height;
}

void CRect::SetPosX(int x)
{
    sdl_rect.x = x;
}

void CRect::SetPosY(int y)
{
    sdl_rect.y = y;
}

void CRect::SetPos(int x, int y)
{
    sdl_rect.x = x;
    sdl_rect.y = y;
}

void CRect::SetPos(const CPos& pos)
{
    sdl_rect.x = pos.GetX();
    sdl_rect.y = pos.GetY();
}

void CRect::SetSDLRect(SDL_Rect _sdl_rect)
{
    sdl_rect = _sdl_rect;
}

CRect CRect::CalcOffset(const CPos& pos) const
{
    CRect calculated_rect(*this);
    calculated_rect.sdl_rect.x = calculated_rect.sdl_rect.x + pos.GetX();
    calculated_rect.sdl_rect.y = calculated_rect.sdl_rect.y + pos.GetY();
    return calculated_rect;
}

CRect CRect::CalcOffset(const CRect& rect) const
{
    CRect calculated_rect(*this);
    calculated_rect.sdl_rect.x = calculated_rect.sdl_rect.x + rect.sdl_rect.x;
    calculated_rect.sdl_rect.y = calculated_rect.sdl_rect.y + rect.sdl_rect.y;
    return calculated_rect;
}

bool CRect::HasPos(CPos pos)
{
    return sdl_rect.x <= pos.GetX() && pos.GetX() <= sdl_rect.x + sdl_rect.w
           && sdl_rect.y <= pos.GetY() && pos.GetY() <= sdl_rect.y + sdl_rect.h;
}

#endif // C_RECT_H
