#ifndef C_UI_TITLE_FIELD_H
#define C_UI_TITLE_FIELD_H

#include "../../lib.h"
#include "../component/CUIComponent.h"
#include "../../common/IObserver.h"
#include "../../common/CColor.h"
#include "../../paint/CPaintRectangle.h"
#include "../../paint/CPaintRectangleBorder.h"
#include "../../paint/CPaintUTF8.h"
#include "../frame/CUIBaseFrame.h"
#include "../../common/CColorPreset.h"

class CUITitleField
    : public CUIComponent,
      public IObserver<CMouseButtonEvent>,
      public IObserver<CMouseMotionEvent>
{
public:
    explicit CUITitleField(CUIBaseFrame& _frame, const CRect& _rect,
                           const string& _label);
    virtual ~CUITitleField();

public:
    const CColor&   GetFgColor();
    void            SetFgColor(const CColor& _fgcolor);
    const CColor&   GetBgColor();
    void            SetBgColor(const CColor& _bgcolor);
    const string&   GetLabel();
    void            SetLabel(const string& _label);
    void            Draw();
    virtual void    OnNotified(CMouseButtonEvent* event);
    virtual void    OnNotified(CMouseMotionEvent* event);
    void            OnMouseLeftButtonDownEvent(const CPos& mouse_pos);
    void            OnMouseLeftButtonUpEvent(const CPos& mouse_pos);
    bool            HasPos(const CPos& pos);
    void            MoveFrameTo(const CPos& pos);

private:
    CColor          fgcolor;
    CColor          bgcolor;
    string          label;
    bool            is_pressed;
    CPos            pressed_pos;
    CPaintRectangle paint_fill;
    CPaintUTF8      paint_utf8;
};

#endif // C_UI_TITLE_FIELD_H
