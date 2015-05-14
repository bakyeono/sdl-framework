#include "./CUIFrameFactory.h"

CUIBaseFrame* CUIFrameFactory::Create(EUIFrameType frame_type, CPos pos)
{
    if (frame_type == EUIFrameType::msgbox)
    {
        CUIMessageBoxFrame* frame =
        new CUIMessageBoxFrame(CRect(550, 200, pos),
                               "메시지 박스",
                               "메시지",
                               "확인", EUIActionType::none);
        return frame;
    }
    if (frame_type == EUIFrameType::msgbox_1)
    {
        CUIMessageBoxFrame* frame =
        new CUIMessageBoxFrame(CRect(550, 200, pos),
                               "메시지박스1 (제목 줄)",
                               "제목 줄을 드래그하면 메시지 창을 옮길 수 있습니다.\n\
메시지 창에 긴 텍스트가 입력되면 창 길이에 맞춰 자동으로 줄이 바뀌어 출력됩니다.",
                               "선택지 1"    , EUIActionType::none,
                               "선택지 2"    , EUIActionType::none);
        return frame;
    }
    if (frame_type == EUIFrameType::msgbox_2)
    {
        CUIMessageBoxFrame* frame =
        new CUIMessageBoxFrame(CRect(550, 120, pos),
                               "뒤풀이",
                               "뒤풀이 장소를 선택하세요.",
                               "뉴 숯불 통닭", EUIActionType::none,
                               "호호통닭"    , EUIActionType::none,
                               "노랑통닭"    , EUIActionType::none,
                               "땡초치킨"    , EUIActionType::none);
        return frame;
    }
    if (frame_type == EUIFrameType::msgbox_3)
    {
        CUIMessageBoxFrame* frame =
        new CUIMessageBoxFrame(CRect(550, 240, pos),
                               "언어에 관해",
                               "프로그램 내부 코드로는 UTF-8을 이용하며, 한글, 히라가나, 카타카나, ASCII 코드를 출력할 수 있습니다. 한자는 출력하지 못합니다.\n\
\n\
わたしがすきなたべものはアイスクリ-ムです.\n\
\n\
They slither wildly as they slip away across the universe.",
                               "닫기"    , EUIActionType::button_close);
        frame->OccupyFocus();
        return frame;
    }
    if (frame_type == EUIFrameType::msgbox_4)
    {
        CUIMessageBoxFrame* frame =
        new CUIMessageBoxFrame(CRect(550, 240, pos),
                               "환영합니다",
                               "박연오의 SDL GUI 프레임워크 데모",
                               "닫기"    , EUIActionType::button_close);
        frame->OccupyFocus();
        return frame;
    }
    else if (frame_type == EUIFrameType::input)
    {
        CUITextInputFrame* frame =
        new CUITextInputFrame(CRect(550, 150, pos),
                              "입력박스 테스트",
                              "그대의 이름은 무엇입니까? (한/영 전환 : [Tab])",
                              "이름: ",
                              "확인"    , EUIActionType::none);
//        frame->OccupyFocus();
        return frame;
    }
    else
    {
        return 0;
    }
}
