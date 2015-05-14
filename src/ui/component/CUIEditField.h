#ifndef C_UI_EDIT_FIELD_H
#define C_UI_EDIT_FIELD_H

#include "../../lib.h"
#include "./CUIComponent.h"
#include "../../common/IObserver.h"
#include "../../common/CColor.h"
#include "../../paint/CPaintRectangle.h"
#include "../../paint/CPaintRectangleBorder.h"
#include "../../paint/CPaintUTF8.h"
#include "../frame/CUIBaseFrame.h"
#include "../../common/CColorPreset.h"
#include "../../util/CKeyboardToUTF8.h"

class CUIEditField
    : public CUIComponent,
      public IObserver<CMouseButtonEvent>,
      public IObserver<CKeyboardEvent>
{
public:
    explicit CUIEditField(CUIBaseFrame& _frame, const CRect& _rect,
                          const string& _label);
    virtual ~CUIEditField();

public:
    int            CalcTextCols();
    const CColor&  GetColor();
    void           SetColor(const CColor& _color);
    const string&  GetText() const;
    void           SetText(const string& text);
    void           Draw();

private:
    virtual void   OnNotified(CMouseButtonEvent* event);
    virtual void   OnNotified(CKeyboardEvent* event);
    void           OnMouseLeftButtonDownEvent(const CPos& mouse_pos);
    bool           HasPos(const CPos& pos);
    void           SetPaintString();

private:
    CColor                 color;
    string                 label;
    int                    text_cols;
    CKeyboardToUTF8        key_to_str;
    CPaintUTF8             paint_utf8;
    CPaintRectangle        paint_line;
};

#endif // C_UI_EDIT_FIELD_H
