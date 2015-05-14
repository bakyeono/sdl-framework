#include "./CPaintRectangle.h"

CPaintRectangle::CPaintRectangle()
{
}

CPaintRectangle::CPaintRectangle(const CRect& _rect, const CColor& _color)
    : CPaint(_rect),
      color(_color)
{
}

CPaintRectangle::~CPaintRectangle()
{
}

const CColor& CPaintRectangle::GetColor() const
{
    return color;
}

void CPaintRectangle::SetColor(const CColor& _color)
{
    color = _color;
}

void CPaintRectangle::Draw(SDL_Surface* dst_surface, CRect dst_rect)
{
    SDL_FillRect(dst_surface,
                 GetRect().CalcOffset(dst_rect).GetSDLRect(),
                 color.GetScreenColor());
}
