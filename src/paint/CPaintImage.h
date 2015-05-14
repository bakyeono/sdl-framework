#ifndef C_PAINT_IMAGE_H
#define C_PAINT_IMAGE_H

#include "../lib.h"
#include "./CPaint.h"
#include "./CImageArray.h"

class CPaintImage
    : public CPaint
{
public:
    explicit CPaintImage();
    explicit CPaintImage(const CRect& _rect, EImageId _image_id);
    virtual ~CPaintImage();

public:
    virtual EImageId  GetImageId() const;
    virtual void      SetImageId(EImageId _image_id);
    virtual void      Draw(SDL_Surface* dst_surface, CRect dst_rect);

private:
    EImageId          image_id;
};

#endif // C_PAINT_IMAGE_H
