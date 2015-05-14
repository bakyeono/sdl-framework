#include "./CUITitleField.h"

CUITitleField::CUITitleField(CUIBaseFrame& _frame, const CRect& _rect,
                             const string& _label)
    : CUIComponent(_frame, _rect),
    fgcolor(CColorPreset::ui_title_fg),
    bgcolor(CColorPreset::ui_title_bg),
    label(_label),
    is_pressed(false),
    paint_fill(_rect, bgcolor),
    paint_utf8(CRect(_rect.GetWidth() - 20,
                     _rect.GetHeight(),
                     _rect.GetPosX() + 10,
                     _rect.GetPosY() + _rect.GetHeight() / 2 - CFont::GetDistFull() / 2),
               CFont(EImageId::font_formal), fgcolor, label)
{
    CSystemEventManager::Instance().RegisterMouseButtonEventObserver(this);
    CSystemEventManager::Instance().RegisterMouseMotionEventObserver(this);
}

CUITitleField::~CUITitleField()
{
    CSystemEventManager::Instance().RemoveMouseButtonEventObserver(this);
    CSystemEventManager::Instance().RemoveMouseMotionEventObserver(this);
}

const CColor& CUITitleField::GetFgColor()
{
    return fgcolor;
}

void CUITitleField::SetFgColor(const CColor& _fgcolor)
{
    fgcolor = _fgcolor;
    paint_utf8.SetColor(fgcolor);
}

const CColor& CUITitleField::GetBgColor()
{
    return bgcolor;
}

void CUITitleField::SetBgColor(const CColor& _bgcolor)
{
    bgcolor = _bgcolor;
    paint_fill.SetColor(bgcolor);
}

const string& CUITitleField::GetLabel()
{
    return label;
}

void CUITitleField::SetLabel(const string& _label)
{
    label = _label;
}

bool CUITitleField::HasPos(const CPos& pos)
{
    if (!GetFrame().GetRect().HasPos(pos))
        return false;
    if (!GetRect().CalcOffset(GetFrame().GetRectOnScreen()).HasPos(pos))
        return false;
    return true;
}

void CUITitleField::Draw()
{
    if (!IsEnabled())
        return;
    if (GetFrame().IsFocused())
    {
        paint_fill.SetColor(CColorPreset::ui_title_focus);
    }
    else
    {
        paint_fill.SetColor(CColorPreset::ui_title_bg);
    }
    paint_fill.Draw(GetFrame().GetSurface(), GetFrame().GetRectOnFrame());
    paint_utf8.Draw(GetFrame().GetSurface(), GetFrame().GetRectOnFrame());
}

void CUITitleField::OnNotified(CMouseMotionEvent* event)
{
    if (!IsEnabled())
        return;
    if (!is_pressed)
        return;
    MoveFrameTo(pressed_pos + event->GetPos());
}

void CUITitleField::MoveFrameTo(const CPos& pos)
{
    GetFrame().SetRect(CRect(GetFrame().GetRect().GetWidth(),
                             GetFrame().GetRect().GetHeight(),
                             pos));
    GetFrame().Update();
}

void CUITitleField::OnNotified(CMouseButtonEvent* event)
{
    if (!IsEnabled())
        return;
    if (event->GetOwner() != &GetFrame())
        return;
    if (event->GetButton() == SDL_BUTTON_LEFT)
    {
        if (event->GetType() == SDL_MOUSEBUTTONDOWN)
        {
            OnMouseLeftButtonDownEvent(event->GetPos());
        }
        else if (event->GetType() == SDL_MOUSEBUTTONUP)
        {
            OnMouseLeftButtonUpEvent(event->GetPos());
        }
    }
}

void CUITitleField::OnMouseLeftButtonDownEvent(const CPos& mouse_pos)
{
    if (is_pressed == false && HasPos(mouse_pos))
    {
        is_pressed = true;
        pressed_pos = GetFrame().GetRect().GetPos() - mouse_pos;
    }
}

void CUITitleField::OnMouseLeftButtonUpEvent(const CPos& mouse_pos)
{
    if (is_pressed == false)
        return;
    is_pressed = false;
}
