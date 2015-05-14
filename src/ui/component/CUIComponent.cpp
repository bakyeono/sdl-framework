#include "./CUIComponent.h"

CUIComponent::CUIComponent(CUIBaseFrame& _frame, const CRect& _rect)
    : frame(_frame),
      rect(_rect),
      is_enabled(true),
      is_focused(false)
{
}

CUIComponent::~CUIComponent()
{
}

void CUIComponent::Draw()
{
}

CRect CUIComponent::GetRect()
{
    return rect;
}

void CUIComponent::SetRect(const CRect& _rect)
{
    rect = _rect;
}

void CUIComponent::Enable()
{
    is_enabled = true;
}

void CUIComponent::Disable()
{
    is_enabled = false;
}

bool CUIComponent::IsEnabled() const
{
    return is_enabled;
}

void CUIComponent::Focus()
{
    is_focused = true;
}

void CUIComponent::Unfocus()
{
    is_focused = false;
}

bool CUIComponent::IsFocused() const
{
    return is_focused;
}

bool CUIComponent::HasPos(const CPos& pos) const
{
    return rect.CalcOffset(frame.GetRectOnScreen()).HasPos(pos);
}

CUIBaseFrame& CUIComponent::GetFrame()
{
    return frame;
}
