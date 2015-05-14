#ifndef C_UI_BUTTON_H
#define C_UI_BUTTON_H

#include "../../lib.h"
#include "./CUIComponent.h"
#include "../../common/IObserver.h"
#include "../../common/CColor.h"
#include "../../paint/CPaintRectangle.h"
#include "../../paint/CPaintRectangleBorder.h"
#include "../../paint/CPaintUTF8.h"
#include "../frame/CUIBaseFrame.h"
#include "../../common/CColorPreset.h"
#include "../action/EUIActionType.h"

class CUIButton
    : public CUIComponent,
      public IObserver<CMouseButtonEvent>
{
public:
    explicit CUIButton(CUIBaseFrame& _frame, const CRect& _rect,
                       const string& _label,
                       EUIActionType _action = EUIActionType::none);
    virtual ~CUIButton();

public:
    const CColor&  GetFgColor();
    void           SetFgColor(const CColor& _fgcolor);
    const CColor&  GetBgColor();
    void           SetBgColor(const CColor& _bgcolor);
    const string&  GetLabel();
    void           SetLabel(const string& _label);
    void           SetAction(EUIActionType _action);
    void           Draw();

private:
    virtual void   OnNotified(CMouseButtonEvent* event);
    void           OnMouseLeftButtonDownEvent(const CPos& mouse_pos);
    void           OnMouseLeftButtonUpEvent(const CPos& mouse_pos);
    void           OnAction();

private:
    CColor                 fgcolor;
    CColor                 bgcolor;
    string                 label;
    EUIActionType          action;
    bool                   is_pressed;
    CPaintRectangle        paint_fill;
    CPaintRectangleBorder  paint_border;
    CPaintUTF8             paint_utf8;
};

#endif // C_UI_BUTTON_H
