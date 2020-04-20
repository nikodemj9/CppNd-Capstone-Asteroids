#include "sound.h"
#include <iostream>
#include <string>


Sound::Sound()
{ 
    SDL_Init(SDL_INIT_AUDIO);
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    LoadMedia(); 
    PlayBackground();    
}

Sound::~Sound()
{
    Mix_FreeMusic(this->background);
    Mix_FreeChunk(shoot);
    Mix_FreeChunk(death);
    Mix_FreeChunk(explosion);
    Mix_CloseAudio();
}

void Sound::LoadMedia()
{
    background = Mix_LoadMUS("media/321019__littlerobotsoundfactory__loop-nothing-can-stop-progress-08.wav");
    shoot = Mix_LoadWAV("media/270343__littlerobotsoundfactory__shoot-01.wav");    
    death = Mix_LoadWAV("media/270328__littlerobotsoundfactory__hero-death-00.wav"); 
    explosion = Mix_LoadWAV("media/270306__littlerobotsoundfactory__explosion-02.wav"); 

    if (background == NULL || shoot == NULL || death == NULL || explosion == NULL)
    {
        std::cout << "Failed to load audio files\n" << (background == NULL) << (shoot == NULL) << (death == NULL) << (explosion == NULL) << "\n";
    }

    Mix_VolumeMusic(8);
    Mix_VolumeChunk(shoot, 10);
    Mix_VolumeChunk(death, 30);
    Mix_VolumeChunk(explosion, 10);
}

void Sound::PlayBackground()
{
    if (background != NULL)
    Mix_PlayMusic(background, -1);
}

void Sound::Play(Mix_Chunk *chunk)
{
    Mix_PlayChannel(-1, chunk, 0);
}