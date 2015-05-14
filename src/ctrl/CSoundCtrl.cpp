#include "CSoundCtrl.h"

const string    CSoundCtrl::conf_sound_path    = "./conf/sound";
const string    CSoundCtrl::conf_music_path    = "./conf/music";

vector<string>  CSoundCtrl::music_filename;

const int       CSoundCtrl::rate               = 22050;
const bool      CSoundCtrl::bit16              = true;
const bool      CSoundCtrl::stereo             = false;
const int       CSoundCtrl::samples            = 512;
const int       CSoundCtrl::number_of_musics   = 15;
int             CSoundCtrl::music_number       = 0;

bool            CSoundCtrl::no_sound           = false;
bool            CSoundCtrl::is_music_started   = false;
bool            CSoundCtrl::is_music_paused    = false;
int             CSoundCtrl::volume             = SDL_MIX_MAXVOLUME;

short int*      CSoundCtrl::buf                = 0;
int             CSoundCtrl::buf_size           = samples * (1+bit16) * (1+stereo);
Uint8*          CSoundCtrl::music_chunk        = 0;
int             CSoundCtrl::music_chunk_size   = 0x1000000;
Uint32          CSoundCtrl::music_len          = 0;
Uint8*          CSoundCtrl::music_head         = 0;
Uint32          CSoundCtrl::music_remain       = 0;
Uint8*          CSoundCtrl::music_at           = 0;


CSoundCtrl::CSoundCtrl()
{
    Init();
}

CSoundCtrl::~CSoundCtrl()
{
}

bool CSoundCtrl::Init()
{
    LoadSoundConf();
    if (no_sound)
        return true;
    SDL_AudioSpec audio;
    audio.freq     = rate;
    audio.format   = bit16  ? AUDIO_S16 : AUDIO_S8;
    audio.channels = stereo ? 2 : 1;
    audio.samples  = buf_size;
    audio.callback = CSoundCtrl::FillMusic;
    audio.userdata = 0;
    buf = new short int[buf_size];
    music_chunk = new Uint8[music_chunk_size];
    if (SDL_OpenAudio(&audio, 0) < 0)
    {
        cout << "[오류] 사운드 초기화 실패: " << SDL_GetError() << endl;
        return false;
    }
    LoadMusicConf();
    return true;
}

bool CSoundCtrl::LoadSoundConf()
{
    ifstream f;
    string   config_item_key;
#ifdef YEONO_DEBUG
    cout << "[진행상황] 사운드 설정 로드" << endl;
#endif // YEONO_DEBUG
    f.open(conf_sound_path.c_str());
    f >> config_item_key >> no_sound;
    cout << config_item_key << " = " << no_sound << endl;
    f.close();
    return true;
}

bool CSoundCtrl::LoadMusicConf()
{
    ifstream f;
    string   config_item_key;
    string   music_path;
#ifdef YEONO_DEBUG
    cout << "[진행상황] 음악 설정 로드" << endl;
#endif // YEONO_DEBUG
    f.open(conf_music_path.c_str());
    for (int i = 0; i<number_of_musics; ++i)
    {
        f >> config_item_key >> music_path;
        cout << config_item_key << " = " << music_path << endl;
        music_filename.push_back(music_path);
    }
    f.close();
    return true;
}

void CSoundCtrl::CleanUp()
{
    if (no_sound)
        return;
    delete [] buf;
    delete [] music_chunk;
    SDL_CloseAudio();
}

void CSoundCtrl::FillMusic(void* udata, Uint8* stream, int len)
{
    if (no_sound)
        return;
    if (music_remain == 0)
    {
        music_remain = music_len;
        music_at = music_head;
    }
    len = (len > (int)music_remain ? music_remain : len);
    SDL_MixAudio(stream, music_at, len, volume);
    music_at += len;
    music_remain -= len;
}

bool CSoundCtrl::LoadAdrib(const string& filename)
{
    if (no_sound)
        return true;
    CEmuopl       opl(rate, bit16, stereo);
//    CTemuopl      opl(rate, bit16, stereo);
    CPlayer*      p = CAdPlug::factory(filename.c_str(), &opl);
    short         buf[buf_size];
    unsigned long towrite;
    unsigned long write;

    if (!p)
    {
        cerr << "[오류] 애드립 파일을 열 수 없습니다 : " << filename << endl;
        return false;
    }
    music_len = 0;
    while (p->update())
    {
        for (towrite = rate / p->getrefresh(); towrite; towrite -= write)
        {
            write = ((int)towrite > buf_size ? buf_size : towrite);
            opl.update(buf, write);
            memcpy(&(music_chunk[music_len]), buf, write*2);
            music_len += write*2;
        }
    }
    music_head = music_chunk;
    music_at = music_head;
    music_remain = music_len;
    return true;
}

int CSoundCtrl::PlayMusicRandom()
{
    if (no_sound)
        return -1;
//    music_number = Random()%number_of_musics;
    music_number = 0;
    PlayMusic(music_number);
    return music_number;
}

void CSoundCtrl::PlayMusic(const int& music_number)
{
    if (no_sound)
        return;
    if (number_of_musics <= music_number)
        return;
    if (is_music_started)
        StopMusic();
    SDL_LockAudio();
    LoadAdrib(music_filename[music_number]);
#ifdef YEONO_DEBUG
    cout << "음악 용량 (" << music_number << ") : " << music_len/1024
    << endl;
#endif // YEONO_DEBUG
    SDL_UnlockAudio();
    SDL_PauseAudio(0);
    is_music_started = true;
    is_music_paused = false;
}

//void CSoundCtrl::FadeOutMusic()
//{
//    if (is_no_sound)
//        return;
//    if (!is_music_started)
//        return;
//    volume = SDL_MIX_MAXVOLUME;
//    fade_timer.Start();
//    while (volume>4)
//    {
//        if(fade_timer.GetTicks() >= 20)
//        {
//            volume *= 0.97;
//            fade_timer.Start();
//        }
//    }
//    fade_timer.Stop();
//    SDL_PauseAudio(1);
//    is_music_started = false;
//    volume = SDL_MIX_MAXVOLUME;
//}
//
void CSoundCtrl::StopMusic()
{
    if (no_sound)
        return;
    if (!is_music_started)
        return;
    SDL_PauseAudio(1);
    is_music_started = false;
}

void CSoundCtrl::PauseMusic()
{
    if (no_sound)
        return;
    if (!is_music_started)
        return;
    if (is_music_paused)
        return;
    SDL_PauseAudio(1);
    is_music_paused = true;
}

void CSoundCtrl::ResumeMusic()
{
    if (no_sound)
        return;
    if (!is_music_started)
        return;
    if (!is_music_paused)
        return;
    SDL_PauseAudio(0);
    is_music_paused = false;
}
