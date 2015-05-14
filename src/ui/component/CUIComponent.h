#ifndef C_UI_COMPONENT_H
#define C_UI_COMPONENT_H

#include "../../lib.h"
#include "../frame/CUIBaseFrame.h"

class CUIComponent
{
public:
    explicit CUIComponent(CUIBaseFrame& _frame, const CRect& _rect);
    virtual ~CUIComponent();
    virtual void Draw();

public:
    virtual CRect     GetRect();
    virtual void      SetRect(const CRect& _rect);
    CUIBaseFrame&     GetFrame();
    void              Enable();
    void              Disable();
    bool              IsEnabled() const;
    void              Focus();
    void              Unfocus();
    bool              IsFocused() const;
    bool              HasPos(const CPos& pos) const;

private:
    CUIBaseFrame& frame;
    CRect     rect;
    bool      is_enabled;
    bool      is_focused;
};

#endif // C_UI_COMPONENT_H
