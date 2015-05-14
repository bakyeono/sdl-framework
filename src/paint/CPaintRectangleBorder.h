#ifndef C_PAINT_RECTANGLE_BORDER_H
#define C_PAINT_RECTANGLE_BORDER_H

#include "../lib.h"
#include "./CPaintRectangle.h"

class CPaintRectangleBorder
    : public CPaintRectangle
{
public:
    explicit CPaintRectangleBorder();
    explicit CPaintRectangleBorder(const CRect& _rect, const CColor& _color, int _thickness);
    virtual ~CPaintRectangleBorder();

public:
    virtual int  GetThickness() const;
    virtual void SetThickness(int _thickness);
    virtual void Draw(SDL_Surface* dst_surface, CRect dst_rect);

private:
    int thickness;
};

#endif // C_PAINT_RECTANGLE_BORDER_H
