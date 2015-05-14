#include "../lib.h"
#include "./CImageArray.h"

CImageArray::CImageArray()
{
#ifdef YEONO_DEBUG
    cout << "[진행상황] 이미지 배열 초기화" << endl;
#endif // YEONO_DEBUG
    Init();
}

CImageArray::~CImageArray()
{
    CleanUp();
}

void CImageArray::Init()
{
    LoadImage("./image/font_formal.png", false);
    LoadImage("./image/font_casual.png", false);
    LoadImage("./image/terrain.png");
    LoadImage("./image/terrain_fog.png");
    LoadImage("./image/wall.png");
    LoadImage("./image/wall_fog.png");
    LoadImage("./image/tree.png");
    LoadImage("./image/tree_fog.png");
    LoadImage("./image/world.png");
    LoadImage("./image/creature.png");
    LoadImage("./image/grid.png");
    LoadImage("./image/illust_0.png");
    LoadImage("./image/illust_1.png");
}

void CImageArray::CleanUp()
{
    for (size_t i = 0; i < image_array.size(); ++i)
    {
        UnloadImage((EImageId)i);
    }
}

bool CImageArray::LoadImage(const string& file_path, bool is_need_to_optimize)
{
    SDL_Surface* loaded_image = 0;
    loaded_image = IMG_Load(file_path.c_str());
    if (loaded_image == 0)
    {
        cerr << "[경고] 이미지 로드 실패 : " << file_path << endl;
        return false;
    }
    if (is_need_to_optimize)
    {
        SDL_Surface* optimized_image = SDL_DisplayFormatAlpha(loaded_image);
        SDL_FreeSurface(loaded_image);
        image_array.push_back(CImage(optimized_image));
    }
    else
    {
        image_array.push_back(CImage(loaded_image));
    }
    return true;
}

void CImageArray::UnloadImage(EImageId id)
{
    if (image_array[(int)id].GetSurface() != 0)
    {
        SDL_FreeSurface(image_array[(int)id].GetSurface());
    }
}
