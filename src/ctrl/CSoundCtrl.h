#ifndef C_SOUND_CTRL_H
#define C_SOUND_CTRL_H

#include "../lib.h"
#include "../adplug/adplug.h"
#include "../adplug/emuopl.h"
#include "../adplug/temuopl.h"

using namespace std;

class CSoundCtrl
{
private:
    explicit CSoundCtrl();
    ~CSoundCtrl();
    CSoundCtrl(const CSoundCtrl&);
    const CSoundCtrl& operator = (const CSoundCtrl&);

public:
    inline static CSoundCtrl&    Instance();

public:
    static void FillMusic(void* udata, Uint8* stream, int len);
    bool LoadAdrib(const string& filename);
    bool LoadMusicFileList();
    bool LoadNoSoundOption();

    bool Init();
    void CleanUp();

    int PlayMusicRandom();
    void PlayMusic(const int& music_number);
    void StopMusic();
    void PauseMusic();
    void ResumeMusic();

private:
//    void FadeOutMusic();
    bool LoadSoundConf();
    bool LoadMusicConf();

private:
    static const string    conf_sound_path;
    static const string    conf_music_path;

    static vector<string>  music_filename;

    static const int       rate;
    static const bool      bit16;
    static const bool      stereo;
    static const int       samples;
    static const int       number_of_musics;
    static int             music_number;

    static bool            no_sound;
    static bool            is_music_started;
    static bool            is_music_paused;
    static int             volume;
//    Timer           fade_timer;

    static short int*      buf;
    static int             buf_size;
    static Uint8*          music_chunk;
    static int             music_chunk_size;
    static Uint32          music_len;
    static Uint8*          music_head;
    static Uint32          music_remain;
    static Uint8*          music_at;
};

CSoundCtrl& CSoundCtrl::Instance()
{
    static CSoundCtrl instance;
    return instance;
}

#endif // C_SOUND_CTRL_H
