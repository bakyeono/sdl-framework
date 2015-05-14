#ifndef C_IMAGE_ARRAY_H
#define C_IMAGE_ARRAY_H

#include "../lib.h"
#include "./CImage.h"
#include "./EImageId.h"

using namespace std;

class CImageArray
{
private:
    explicit CImageArray();
    ~CImageArray();

public:
    inline static CImageArray&   Instance();

public:
    inline CImage                GetImage(EImageId id);

private:
    void                  Init();
    void                  CleanUp();
    bool                  LoadImage(const string& file_path,
                                    bool is_need_to_optimize = true);
    void                  UnloadImage(EImageId EImageId);

private:
    vector<CImage>        image_array;
};

CImage CImageArray::GetImage(EImageId id)
{
#ifdef YEONO_DEBUG
    if (image_array.size() <= (int)id)
    {
        cerr << "[경고] 이미지 배열 오버플로 : " << (int)id << endl;
    }
#endif // YEONO_DEBUG
    return image_array[(int)id];
}

CImageArray& CImageArray::Instance()
{
    static CImageArray instance;
    return instance;
}

#endif // C_IMAGE_ARRAY_H
