#pragma once
#include <thread>
#include <memory>
#include <SDL.h>
#include <SDL_mixer.h>


class Sound{
public:
    Sound();
    ~Sound();
    void Play(Mix_Chunk *chunk);

    Mix_Chunk *shoot{NULL};
    Mix_Chunk *death{NULL};
    Mix_Chunk *explosion{NULL};
private:
    void LoadMedia();
    void PlayBackground();
    Mix_Music *background{NULL};
    
};