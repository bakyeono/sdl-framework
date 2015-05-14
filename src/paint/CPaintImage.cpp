#include "./CPaintImage.h"

CPaintImage::CPaintImage()
{
}

CPaintImage::CPaintImage(const CRect& _rect, EImageId _image_id)
    : CPaint(_rect),
      image_id(_image_id)
{
}

CPaintImage::~CPaintImage()
{
}

EImageId CPaintImage::GetImageId() const
{
    return image_id;
}

void CPaintImage::SetImageId(EImageId _image_id)
{
    image_id = _image_id;
}

void CPaintImage::Draw(SDL_Surface* dst_surface, CRect dst_rect)
{
    CImageArray::Instance().GetImage(image_id).Draw(dst_surface,
            GetRect().CalcOffset(dst_rect));
}
