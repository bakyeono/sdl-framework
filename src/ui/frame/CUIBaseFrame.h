#ifndef C_UI_BASE_FRAME_H
#define C_UI_BASE_FRAME_H

#include "../../lib.h"
#include "./IUIFrame.h"
#include "../../common/CColor.h"
#include "../../common/CColorPreset.h"
#include "../../paint/CPaintRectangle.h"
#include "../../event/CSystemEventManager.h"
#include "../../paint/CPaintRectangleBorder.h"
#include "../CUIManager.h"

class CUIBaseFrame
    : public IUIFrame
{
public:
    explicit CUIBaseFrame(const CRect& _rect, bool _is_occupying_focus = false);
    virtual ~CUIBaseFrame();

public:
    Uint32                    GetAccessClock() const;
    void                      OnNotified(CMouseButtonEvent* event);
    void                      OnNotified(CVideoResizeEvent* event);
    void                      Draw();
    CRect                     GetRect();
    void                      SetRect(const CRect& _rect);
    CRect                     GetRectOnScreen();
    CRect                     GetRectOnFrame();
    void                      AffectRectChange();
    SDL_Surface*              GetSurface();
    const CColor&             GetFgColor();
    void                      SetFgColor(const CColor& _fgcolor);
    const CColor&             GetBgColor();
    void                      SetBgColor(const CColor& _bgcolor);
    bool                      HasPos(const CPos& pos);
    bool                      IsUpdated() const;
    void                      Update();
    void                      Outdate();
    bool                      IsEnabled() const;
    void                      Disable();
    bool                      IsFocused() const;
    void                      Focus();
    void                      Unfocus();
    bool                      IsOccupyingFocus() const;
    void                      OccupyFocus();
    void                      UnoccupyFocus();
    void                      FixToInsideOfScreen();

protected:
    void                      DrawPrepare();
    virtual void              DrawComponents();
    void                      DrawFinish();

private:
    Uint32                    access_clock;
    CRect                     rect;
    CRect                     rect_on_screen;
    CRect                     rect_on_frame;
    CColor                    fgcolor;
    CColor                    bgcolor;
    SDL_Surface*              surface;
    bool                      is_updated;
    bool                      is_enabled;
    bool                      is_focused;
    bool                      is_occupying_focus;
    CPaintRectangle           paint_fill;
    CPaintRectangleBorder     paint_border;
};

#endif // C_UI_BASE_FRAME_H
