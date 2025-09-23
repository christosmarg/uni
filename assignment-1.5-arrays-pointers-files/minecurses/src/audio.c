#include "audio.h"

void *play_audio(void *threadid)
{
    /*int tid = (long)threadid;*/
    Mix_Music *music = NULL;
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 4096);
    music = Mix_LoadMUS(AUDIO_PATH);

    Mix_PlayMusic(music, -1);
    while (Mix_PlayingMusic()) ;
    Mix_FreeMusic(music);
    Mix_CloseAudio();
}

void volume(char option)
{
    static int volume = MIX_MAX_VOLUME;

    switch (option)
    {
        case '+':
            if (volume == MIX_MAX_VOLUME) break;
            else Mix_VolumeMusic(volume += 10);
            break;
        case '-':
            if (volume == 0) break;
            else Mix_VolumeMusic(volume -= 10);
            break;
    }
}

void pause_audio(void)
{
	(Mix_PausedMusic() == 1) ? Mix_ResumeMusic() : Mix_PauseMusic();
}
