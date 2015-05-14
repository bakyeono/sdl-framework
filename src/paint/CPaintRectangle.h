#ifndef C_PAINT_RECTANGLE_H
#define C_PAINT_RECTANGLE_H

#include "../lib.h"
#include "../common/CColor.h"
#include "./CPaint.h"

class CPaintRectangle
    : public CPaint
{
public:
    explicit CPaintRectangle();
    explicit CPaintRectangle(const CRect& _rect, const CColor& _color);
    virtual ~CPaintRectangle();

public:
    virtual const CColor& GetColor() const;
    virtual void          SetColor(const CColor& _color);
    virtual void          Draw(SDL_Surface* dst_surface, CRect dst_rect);

private:
    CColor color;
};

#endif // C_PAINT_RECTANGLE_H
