#include "./CPaint.h"

CPaint::CPaint()
    : rect(CRect(0, 0, 0, 0))
{
}

CPaint::CPaint(const CRect& _rect)
    : rect(_rect)
{
}

CPaint::~CPaint()
{
}

CRect CPaint::GetRect() const
{
    return rect;
}

void CPaint::SetRect(const CRect& _rect)
{
    rect = _rect;
}

