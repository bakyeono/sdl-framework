#ifndef C_UI_TEXT_FIELD_H
#define C_UI_TEXT_FIELD_H

#include "../../lib.h"
#include "./CUIComponent.h"
#include "../../common/IObserver.h"
#include "../../common/CColor.h"
#include "../../paint/CPaintRectangle.h"
#include "../../paint/CPaintRectangleBorder.h"
#include "../../paint/CPaintUTF8.h"
#include "../frame/CUIBaseFrame.h"
#include "../../common/CColorPreset.h"

class CUITextField
    : public CUIComponent
{
public:
    explicit CUITextField(CUIBaseFrame& _frame, const CRect& _rect, const string& text);
    virtual ~CUITextField();

public:
    void               InitTextArray();
    int                CalcTextCols();
    int                CalcTextRows();
    const CColor&      GetTextColor();
    void               SetTextColor(const CColor& text_color);
    void               SetText(const string& text);
    void               Draw();

private:
    CColor             text_color;
    vector<CPaintUTF8> text_array;
    int                text_cols;
    int                text_rows;
};

#endif // C_UI_TEXT_FIELD_H
