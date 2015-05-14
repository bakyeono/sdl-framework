#include "./CUIBaseFrame.h"

CUIBaseFrame::CUIBaseFrame(const CRect& _rect, bool _is_occupying_focus)
    : rect(_rect),
      rect_on_screen(CRect(CScreenCtrl::Instance().GetWidth(),
                           CScreenCtrl::Instance().GetHeight(),
                           rect.GetPos())),
      rect_on_frame(CRect(rect.GetWidth(), rect.GetHeight(), CPos(0, 0))),
      fgcolor(CColorPreset::ui_frame_fg),
      bgcolor(CColorPreset::ui_frame_bg),
      surface(0),
      is_updated(true),
      is_enabled(true),
      is_focused(false),
      is_occupying_focus(_is_occupying_focus),
      paint_fill(CPaintRectangle(CRect(rect.GetWidth(), rect.GetHeight(), CPos(0, 0)), bgcolor)),
      paint_border(CPaintRectangleBorder(CRect(rect.GetWidth(), rect.GetHeight(), CPos(0, 0)), fgcolor, 2))
{
    surface = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                   rect.GetWidth(), rect.GetHeight(),
                                   CScreenCtrl::Instance().GetBPP(),
                                   0, 0, 0, 0);
    if (surface == 0)
    {
        cerr << "[오류] RGBSurface 생성 실패" << endl;
    }
    CSystemEventManager::Instance().RegisterEventOwnerInfo(this);
    CSystemEventManager::Instance().RegisterMouseButtonEventObserver(this);
    CSystemEventManager::Instance().RegisterVideoResizeEventObserver(this);
    access_clock = SDL_GetTicks();
    if (is_occupying_focus) is_focused = true;
}

CUIBaseFrame::~CUIBaseFrame()
{
    if (surface != 0)
    {
        SDL_FreeSurface(surface);
    }
    CSystemEventManager::Instance().RemoveEventOwnerInfo(this);
    CSystemEventManager::Instance().RemoveMouseButtonEventObserver(this);
    CSystemEventManager::Instance().RemoveVideoResizeEventObserver(this);
}

CRect CUIBaseFrame::GetRect()
{
    return rect;
}

CRect CUIBaseFrame::GetRectOnScreen()
{
    return rect_on_screen;
}

CRect CUIBaseFrame::GetRectOnFrame()
{
    return rect_on_frame;
}

void CUIBaseFrame::SetRect(const CRect& _rect)
{
    rect = _rect;
    FixToInsideOfScreen();
    AffectRectChange();
    Update();
}

void CUIBaseFrame::AffectRectChange()
{
    rect_on_screen = CRect(CScreenCtrl::Instance().GetWidth(),
                           CScreenCtrl::Instance().GetHeight(),
                           rect.GetPos());
    rect_on_frame  = CRect(rect.GetWidth(),
                           rect.GetHeight(),
                           CPos(0, 0));
}

const CColor& CUIBaseFrame::GetFgColor()
{
    return fgcolor;
}

void CUIBaseFrame::SetFgColor(const CColor& _fgcolor)
{
    fgcolor = _fgcolor;
    paint_border.SetColor(fgcolor);
}

const CColor& CUIBaseFrame::GetBgColor()
{
    return bgcolor;
}

void CUIBaseFrame::SetBgColor(const CColor& _bgcolor)
{
    bgcolor = _bgcolor;
    paint_fill.SetColor(bgcolor);
}

void CUIBaseFrame::Draw()
{
    if (!IsEnabled())
    {
        return;
    }
    else if (!IsUpdated())
    {
//        cout << (size_t) this << " -- draw (simple copy)" << endl;
        DrawFinish();
        return;
    }
    else
    {
//        cout << (size_t) this << " -- draw (complex)" << endl;
        DrawPrepare();
        DrawComponents();
        DrawFinish();
    }
}

void CUIBaseFrame::DrawPrepare()
{
    paint_fill.Draw(surface, rect_on_frame);
    paint_border.Draw(surface, rect_on_frame);
}

void CUIBaseFrame::DrawComponents()
{
}

void CUIBaseFrame::DrawFinish()
{
    SDL_BlitSurface(surface,
                    0,
                    CScreenCtrl::Instance().GetSurface(),
                    rect_on_screen.GetSDLRect());
    Outdate();
}

void CUIBaseFrame::Update()
{
    is_updated = true;
    CUIManager::Instance().ReserveRefresh();
}

void CUIBaseFrame::Outdate()
{
    is_updated = false;
}

void CUIBaseFrame::Disable()
{
    is_enabled = false;
}

bool CUIBaseFrame::HasPos(const CPos& pos)
{
    return rect.HasPos(pos);
}

void CUIBaseFrame::OnNotified(CMouseButtonEvent* event)
{
    if (!IsEnabled())
        return;
    if (event->GetOwner()  == this &&
        event->GetButton() == SDL_BUTTON_LEFT &&
        event->GetType()   == SDL_MOUSEBUTTONDOWN)
    {
        access_clock = SDL_GetTicks();
    }
}

bool CUIBaseFrame::IsUpdated() const
{
    return is_updated;
}

bool CUIBaseFrame::IsEnabled() const
{
    return is_enabled;
}

bool CUIBaseFrame::IsFocused() const
{
    return is_focused;
}

void CUIBaseFrame::Focus()
{
    if (!is_focused)
    {
        is_focused = true;
        Update();
    }
}

void CUIBaseFrame::Unfocus()
{
    if (is_focused)
    {
        is_focused = false;
        Update();
    }
}

bool CUIBaseFrame::IsOccupyingFocus() const
{
    return is_occupying_focus;
}

void CUIBaseFrame::OccupyFocus()
{
    is_occupying_focus = true;
}

void CUIBaseFrame::UnoccupyFocus()
{
    is_occupying_focus = false;
}

SDL_Surface* CUIBaseFrame::GetSurface()
{
    return surface;
}

Uint32 CUIBaseFrame::GetAccessClock() const
{
    return access_clock;
}

void CUIBaseFrame::FixToInsideOfScreen()
{
    if (rect.GetPosX() < 0)
    {
        rect.SetPosX(0);
    }
    else if (CScreenCtrl::Instance().GetWidth() <= rect.GetPosX() + rect.GetWidth())
    {
        rect.SetPosX(CScreenCtrl::Instance().GetWidth() - rect.GetWidth());
    }
    if (rect.GetPosY() < 0)
    {
        rect.SetPosY(0);
    }
    else if (CScreenCtrl::Instance().GetHeight() <= rect.GetPosY() + rect.GetHeight())
    {
        rect.SetPosY(CScreenCtrl::Instance().GetHeight() - rect.GetHeight());
    }
    AffectRectChange();
}

void CUIBaseFrame::OnNotified(CVideoResizeEvent* event)
{
    FixToInsideOfScreen();
    AffectRectChange();
    Update();
}
