#include "./CScreenCtrl.h"

CScreenCtrl::CScreenCtrl()
    : surface(0),
      default_width(800),
      default_height(600),
      bpp(32),
      fullscreen(false),
      noframe(false),
      videomemory(false),
      resizeable(true)
{
    Init();
}

CScreenCtrl::~CScreenCtrl()
{
}
