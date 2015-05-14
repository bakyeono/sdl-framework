#include "./CUIMessageBoxFrame.h"

CUIMessageBoxFrame::CUIMessageBoxFrame(const CRect& _rect,
                                       const string& title_label,
                                       const string& message_text,
                                       const string& button1_label,
                                       EUIActionType button1_action,
                                       const string& button2_label,
                                       EUIActionType button2_action,
                                       const string& button3_label,
                                       EUIActionType button3_action,
                                       const string& button4_label,
                                       EUIActionType button4_action)
    : CUIBaseFrame(_rect),
      title(CUITitleField(*this, CRect(_rect.GetWidth(), 24, 0, 8), title_label)),
      message(CUITextField(*this, CRect(_rect.GetWidth()-40, _rect.GetHeight()-64, 20, 44), message_text)),
      button1(CUIButton(*this, CRect(130, 22, 8, _rect.GetHeight()-32), button1_label, button1_action)),
      button2(CUIButton(*this, CRect(130, 22, 142, _rect.GetHeight()-32), button2_label, button2_action)),
      button3(CUIButton(*this, CRect(130, 22, 278, _rect.GetHeight()-32), button3_label, button3_action)),
      button4(CUIButton(*this, CRect(130, 22, 413, _rect.GetHeight()-32), button4_label, button4_action))
{
    if (button1.GetLabel().empty())
        button1.Disable();
    if (button2.GetLabel().empty())
        button2.Disable();
    if (button3.GetLabel().empty())
        button3.Disable();
    if (button4.GetLabel().empty())
        button4.Disable();
}

CUIMessageBoxFrame::~CUIMessageBoxFrame()
{
}

void CUIMessageBoxFrame::DrawComponents()
{
    title.Draw();
    message.Draw();
    button1.Draw();
    button2.Draw();
    button3.Draw();
    button4.Draw();
}
