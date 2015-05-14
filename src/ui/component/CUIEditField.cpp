#include "./CUIEditField.h"

CUIEditField::CUIEditField(CUIBaseFrame& _frame, const CRect& _rect,
                           const string& _label)
    : CUIComponent(_frame, _rect),
      color(CColorPreset::ui_title_fg),
      label(_label),
      key_to_str(EInputMode::korean_2pair, true, false, true, CalcTextCols(), ""),
      paint_utf8(CPaintUTF8(_rect,
                            CFont(EImageId::font_casual),
                            CColorPreset::ui_text,
                            "")),
      paint_line(CPaintRectangle(CRect(_rect.GetWidth(), 1, _rect.GetPosX(), _rect.GetPosY() + _rect.GetHeight() - 2),
                                 CColorPreset::ui_text))
{
    CSystemEventManager::Instance().RegisterMouseButtonEventObserver(this);
    CSystemEventManager::Instance().RegisterKeyboardEventObserver(this);
    SetPaintString();
}

CUIEditField::~CUIEditField()
{
    CSystemEventManager::Instance().RemoveMouseButtonEventObserver(this);
    CSystemEventManager::Instance().RemoveKeyboardEventObserver(this);
}

int CUIEditField::CalcTextCols()
{
    return GetRect().GetWidth() / CFont::GetDistHalf() - CUTF8Util::MonoLength(label);
}

const CColor& CUIEditField::GetColor()
{
    return color;
}

void CUIEditField::SetColor(const CColor& _color)
{
    color = _color;
    paint_utf8.SetColor(color);
    paint_line.SetColor(color);
}

const string& CUIEditField::GetText() const
{
    return key_to_str.GetString();
}

void CUIEditField::SetText(const string& text)
{
    key_to_str.SetString(text);
    SetPaintString();
}

void CUIEditField::Draw()
{
    if (!IsEnabled())
        return;
    paint_line.Draw(GetFrame().GetSurface(), GetFrame().GetRectOnFrame());
    paint_utf8.Draw(GetFrame().GetSurface(), GetFrame().GetRectOnFrame());
}

bool CUIEditField::HasPos(const CPos& pos)
{
    return GetRect().CalcOffset(GetFrame().GetRectOnScreen()).HasPos(pos);
}

void CUIEditField::OnNotified(CMouseButtonEvent* event)
{
    if (!IsEnabled())                             return;
    if (!event->GetButton() == SDL_BUTTON_LEFT)   return;
    if (!event->GetType() == SDL_MOUSEBUTTONDOWN) return;
    if (event->GetOwner() != &GetFrame())         return;
    OnMouseLeftButtonDownEvent(event->GetPos());
}

void CUIEditField::OnMouseLeftButtonDownEvent(const CPos& mouse_pos)
{
    if (!HasPos(mouse_pos)) return;
    Focus();
    SetPaintString();
    GetFrame().Update();
}

void CUIEditField::OnNotified(CKeyboardEvent* event)
{
    if (!GetFrame().IsFocused())       return;
    if (!IsFocused())                  return;
    if (!IsEnabled())                  return;
    if (event->GetType() == SDL_KEYUP) return;
    key_to_str.ProcessKey(event->GetKeycode());
    SetPaintString();
    GetFrame().Update();
}

void CUIEditField::SetPaintString()
{
    if (IsFocused())
    {
        paint_utf8.SetString(label + key_to_str.GetString() + '_');
    }
    else
    {
        paint_utf8.SetString(label + key_to_str.GetString());
    }
}
