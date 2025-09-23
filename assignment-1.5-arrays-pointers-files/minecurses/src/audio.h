#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "minesweeper.h"

#define AUDIO_PATH "res/detective-8bit.wav"

void *play_audio(void *threadid);
void volume		(char);
void pause_audio(void);

#endif /* AUDIO_H */
