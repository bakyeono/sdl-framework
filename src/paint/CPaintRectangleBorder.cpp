#include "./CPaintRectangleBorder.h"

CPaintRectangleBorder::CPaintRectangleBorder()
{
}

CPaintRectangleBorder::CPaintRectangleBorder(const CRect& _rect,
                                             const CColor& _color,
                                             int _thickness)
    : CPaintRectangle(_rect, _color),
      thickness(_thickness)
{
}

CPaintRectangleBorder::~CPaintRectangleBorder()
{
}

int CPaintRectangleBorder::GetThickness() const
{
    return thickness;
}

void CPaintRectangleBorder::SetThickness(int _thickness)
{
    thickness = _thickness;
}

void CPaintRectangleBorder::Draw(SDL_Surface* dst_surface, CRect dst_rect)
{
    CPaintRectangle paint;
    paint.SetColor(GetColor());
    paint.SetRect(CRect(thickness, GetRect().GetHeight(), GetRect().GetPos()));
    paint.Draw(dst_surface, dst_rect);
    paint.SetRect(CRect(GetRect().GetWidth(), thickness, GetRect().GetPos()));
    paint.Draw(dst_surface, dst_rect);
    paint.SetRect(CRect(thickness, GetRect().GetHeight(),
                        GetRect().GetPosX() + GetRect().GetWidth() - thickness,
                        GetRect().GetPosY()));
    paint.Draw(dst_surface, dst_rect);
    paint.SetRect(CRect(GetRect().GetWidth(), thickness,
                        GetRect().GetPosX(),
                        GetRect().GetPosY() + GetRect().GetHeight() - thickness));
    paint.Draw(dst_surface, dst_rect);
}
