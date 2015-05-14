#ifndef C_PAINT_IMAGE_PATTERN_H
#define C_PAINT_IMAGE_PATTERN_H

#include "../lib.h"
#include "./CPaintImage.h"

class CPaintImagePattern
    : public CPaintImage
{
public:
    explicit CPaintImagePattern();
    explicit CPaintImagePattern(const CRect& _rect, EImageId _image_id);
    virtual ~CPaintImagePattern();

public:
    virtual void Draw(SDL_Surface* dst_surface, CRect dst_rect);
};

#endif // C_PAINT_IMAGE_PATTERN_H
