#include "./lib.h"
#include "./ctrl/CScreenCtrl.h"
#include "./paint/CImageArray.h"
#include "./ui/CUIManager.h"
#include "./ui/frame/CUIFrameFactory.h"
#include "./ui/frame/EUIFrameType.h"
#include "./paint/CTileset.h"
#include "./ctrl/CSoundCtrl.h"
#include "./util/CRand.h"


using namespace std;

const string  window_caption("GUI 프레임워크");

CTileset tileset(EImageId::tileset_terrain,
                 40, 22, 16, 34, 40, 20, 15, 14, 0, 0);

void InitSDL()
{
#ifdef YEONO_DEBUG
    cout << "[진행상황] SDL 초기화" << endl;
#endif // YEONO_DEBUG
    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO) == -1)
    {
        cerr << "[오류] SDL 초기화 실패 : " << SDL_GetError() << endl;
        exit(1);
    }
}

void CleanUpSDL()
{
#ifdef YEONO_DEBUG
    cout << "[진행상황] SDL 종료" << endl;
#endif // YEONO_DEBUG
    SDL_Quit();
}

bool InitWindowIcon()
{
#ifdef YEONO_DEBUG
    cout << "[진행상황] 아이콘 설정" << endl;
#endif // YEONO_DEBUG
    //SDL_WM_SetIcon();
    return true;
}

void InitWindowCaption()
{
    SDL_WM_SetCaption(window_caption.c_str(), 0);
}

bool InitUnicode()
{
#ifdef YEONO_DEBUG
    cout << "[진행상황] 유니코드 설정" << endl;
#endif // YEONO_DEBUG
    if (SDL_EnableUNICODE(SDL_ENABLE))
    {
        cerr << "[오류] 유니코드 설정 실패" << endl;
        return false;
    }
    else
    {
        return true;
    }
}

void InitScreen()
{
#ifdef YEONO_DEBUG
    cout << "[진행상황] 스크린 초기화" << endl;
#endif // YEONO_DEBUG
    CScreenCtrl::Instance();
}

void InitImageArray()
{
    CImageArray::Instance();
}

void InitProcess()
{
    InitSDL();
    InitWindowCaption();
    InitUnicode();
    InitScreen();
    InitImageArray();
    InitWindowIcon();
    const int key_repeat_delay = 140;
    const int key_repeat_interval = 60;
    SDL_EnableKeyRepeat(key_repeat_delay, key_repeat_interval);
}

void CleanUpProcess()
{
    CleanUpSDL();
}

int main(int argc, char** args)
{
    InitProcess();
    CUIManager::Instance().RegisterFrame(CUIFrameFactory::Create(EUIFrameType::msgbox_1, CPos(40, 40)));
    CUIManager::Instance().RegisterFrame(CUIFrameFactory::Create(EUIFrameType::msgbox_2, CPos(80, 80)));
    CUIManager::Instance().RegisterFrame(CUIFrameFactory::Create(EUIFrameType::msgbox_3, CPos(120, 120)));
    CUIManager::Instance().RegisterFrame(CUIFrameFactory::Create(EUIFrameType::input, CPos(160, 160)));
    CUIManager::Instance().RegisterFrame(CUIFrameFactory::Create(EUIFrameType::msgbox_4, CPos(200, 200)));

    CSoundCtrl::Instance().PlayMusic(0);

    CUIManager::Instance().Run();


    CleanUpProcess();
    return CExitCtrl::GetExitStatus();
}
