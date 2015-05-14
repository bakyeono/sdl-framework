#include "./CUITextInputFrame.h"

CUITextInputFrame::CUITextInputFrame(const CRect& _rect,
                                     const string& title_label,
                                     const string& message_text,
                                     const string& edit_label,
                                     const string& button_label,
                                     EUIActionType button_action)
    : CUIBaseFrame(_rect),
      title(CUITitleField(*this, CRect(_rect.GetWidth(), 24, 0, 8), title_label)),
      message(CUITextField(*this, CRect(_rect.GetWidth()-40, _rect.GetHeight()-64, 20, 44), message_text)),
      edit(CUIEditField(*this, CRect(_rect.GetWidth()-40, 20, 20, _rect.GetHeight()-70), edit_label)),
      button(CUIButton(*this, CRect(130, 22, 8, _rect.GetHeight()-32), button_label, button_action))
{
    if (button.GetLabel().empty())
        button.Disable();
}

CUITextInputFrame::~CUITextInputFrame()
{
}

void CUITextInputFrame::DrawComponents()
{
    title.Draw();
    message.Draw();
    edit.Draw();
    button.Draw();
}
