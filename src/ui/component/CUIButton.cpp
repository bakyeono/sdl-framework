#include "./CUIButton.h"

CUIButton::CUIButton(CUIBaseFrame& _frame, const CRect& _rect,
                     const string& _label, EUIActionType _action)
    : CUIComponent(_frame, _rect),
      fgcolor(CColorPreset::ui_component_fg),
      bgcolor(CColorPreset::ui_component_bg),
      label(_label),
      action(_action),
      is_pressed(false),
      paint_fill(_rect, bgcolor),
      paint_border(_rect, fgcolor, 2),
      paint_utf8(CRect(_rect.GetWidth() - 20,
                       _rect.GetHeight(),
                       _rect.GetPosX() + 10,
                       _rect.GetPosY() + _rect.GetHeight()/2 - CFont::GetDistFull()/2),
                 CFont(EImageId::font_formal), fgcolor, label)
{
    CSystemEventManager::Instance().RegisterMouseButtonEventObserver(this);
}

CUIButton::~CUIButton()
{
    CSystemEventManager::Instance().RemoveMouseButtonEventObserver(this);
}

const CColor& CUIButton::GetFgColor()
{
    return fgcolor;
}

void CUIButton::SetFgColor(const CColor& _fgcolor)
{
    fgcolor = _fgcolor;
    paint_border.SetColor(fgcolor);
    paint_utf8.SetColor(fgcolor);
}

const CColor& CUIButton::GetBgColor()
{
    return bgcolor;
}

void CUIButton::SetBgColor(const CColor& _bgcolor)
{
    bgcolor = _bgcolor;
    paint_fill.SetColor(bgcolor);
}

const string& CUIButton::GetLabel()
{
    return label;
}

void CUIButton::SetLabel(const string& _label)
{
    label = _label;
}

void CUIButton::SetAction(EUIActionType _action)
{
    action = _action;
}

void CUIButton::Draw()
{
    if (!IsEnabled())
        return;
    if (is_pressed == false)
    {
        paint_border.SetThickness(2);
    }
    else
    {
        paint_border.SetThickness(4);
    }
    paint_fill.Draw(GetFrame().GetSurface(), GetFrame().GetRectOnFrame());
    paint_border.Draw(GetFrame().GetSurface(), GetFrame().GetRectOnFrame());
    paint_utf8.Draw(GetFrame().GetSurface(), GetFrame().GetRectOnFrame());
}

void CUIButton::OnNotified(CMouseButtonEvent* event)
{
    if (!IsEnabled()) return;
    if (!event->GetButton() == SDL_BUTTON_LEFT) return;
    if (event->GetType() == SDL_MOUSEBUTTONDOWN)
    {
        if (event->GetOwner() != &GetFrame()) return;
        OnMouseLeftButtonDownEvent(event->GetPos());
    }
    else if (event->GetType() == SDL_MOUSEBUTTONUP)
    {
        OnMouseLeftButtonUpEvent(event->GetPos());
    }
}

void CUIButton::OnMouseLeftButtonDownEvent(const CPos& mouse_pos)
{
    if (is_pressed == false && HasPos(mouse_pos))
    {
        is_pressed = true;
        GetFrame().Update();
    }
}

void CUIButton::OnMouseLeftButtonUpEvent(const CPos& mouse_pos)
{
    if (is_pressed == false) return;
    is_pressed = false;
    if (HasPos(mouse_pos))
        OnAction();
    GetFrame().Update();
}

//void CUIButton::OnMouseRightButtonDownEvent(const CPos& mouse_pos)
//{
//    ;
//}
//
//void CUIButton::OnMouseRightButtonUpEvent(const CPos& mouse_pos)
//{
//    ;
//}
//
void CUIButton::OnAction()
{
    if (action == EUIActionType::none) return;
    if (action == EUIActionType::button_close) GetFrame().Disable();
}
