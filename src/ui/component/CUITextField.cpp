#include "./CUITextField.h"

CUITextField::CUITextField(CUIBaseFrame& _frame, const CRect& _rect,
                           const string& text)
    : CUIComponent(_frame, _rect),
      text_color(CColorPreset::ui_title_fg),
      text_cols(CalcTextCols()),
      text_rows(CalcTextRows())
{
    InitTextArray();
    SetText(text);
}

CUITextField::~CUITextField()
{
}

void CUITextField::InitTextArray()
{
    text_array.clear();
    CRect line_rect(GetRect());
    line_rect.SetHeight(CFont::GetFontHeight());
    for (int i = 0; i < text_rows; ++i)
    {
        text_array.push_back(CPaintUTF8(line_rect, CFont(EImageId::font_casual), CColorPreset::ui_text));
        line_rect.SetPosY(line_rect.GetPosY() + CFont::GetDistLine());
    }
}

int CUITextField::CalcTextCols()
{
    return GetRect().GetWidth() / CFont::GetDistHalf();
}

int CUITextField::CalcTextRows()
{
    return GetRect().GetHeight() / CFont::GetDistLine();
}

const CColor& CUITextField::GetTextColor()
{
    return text_color;
}

void CUITextField::SetTextColor(const CColor& _text_color)
{
    text_color = _text_color;
    for (int i = 0; i < text_rows; ++i)
    {
        text_array[i].SetColor(text_color);
    }
}

void CUITextField::SetText(const string& text)
{
    int from = 0;
    int to = 0;
    for (int i = 0; i < text_rows; ++i)
    {
        to = CUTF8Util::FindNextLinePoint(text, from, text_cols);
        text_array[i].SetString(text.substr(from, to - from));
        from = to;
    }
}

void CUITextField::Draw()
{
    if (!IsEnabled())
        return;
    for (int i = 0; i < text_rows; ++i)
    {
        text_array[i].Draw(GetFrame().GetSurface(), GetFrame().GetRectOnFrame());
    }
}
