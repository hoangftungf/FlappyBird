#include "sound.h"
#include <stdio.h>
#include <iostream>
#include <string>

bool sound::init()
{
    string breath_path = "res/sound/sfx_breath.wav";
    string hit_path = "res/sound/sfx_bonk.wav";
    string point_path = "res/sound/sfx_point.wav"; 
    string sound_path = "res/image/sound.png";

    bool success = true;

    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        cout << "SDL not init! SDL Error \n";
        success = false;
    }
    else
    {
        if( Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0 )
        {
            cout << "SDL_mixer not open! SDL_mixer Errror \n";
            success = false;
        }

        breath = Mix_LoadWAV( breath_path.c_str() );
        if ( breath == NULL )
        {
            cout << "SDL not load sound ! SDL_mixer Error \n";
            success = false;
        }

        hit = Mix_LoadWAV( hit_path.c_str() );
        if (hit == NULL)
        {
            cout<< "SDL not load sound! SDL_mixer Errror \n";
            success = false;
        }

        point = Mix_LoadWAV(point_path.c_str());
        if (point == NULL)
        {
            cout << "SDL not load sound! SDL_mixer Errror \n";
            success = false;
        }

        if (!Load(sound_path))
        {
            return false;
        }

        Active.x = 0; Active.y = 0; Active.w = getWidth(); Active.h = getHeight() / 2;
        Mute.x = 0; Mute.y = getHeight() / 2; Mute.w = getWidth(); Mute.h = getHeight() / 2;
        isPlay = true;
    }
    return success;
}

void sound::Free()
{
    free();

    Mix_FreeChunk(breath);
    breath = NULL;
    Mix_FreeChunk(hit);
    hit = NULL;
    Mix_FreeChunk(point);
    point = NULL;
    Mix_Quit();
}

void sound::playBreath()
{
    if (isPlay)
    {
        Mix_PlayChannel( -1, breath, 0 );
    }
}

void sound::playHit()
{
    if (isPlay)
    {
        Mix_PlayChannel(-1, hit, 0);
    }
}

void sound::playPoint()
{
    if (isPlay)
    {
        Mix_PlayChannel(-1, point, 0);
    }
}

void sound::renderSound()
{
    if (isPlay)
    {
        Render(POS_X, POS_Y, 0, &Active);
    }
    else
    {
        Render(POS_X, POS_Y, 0, &Mute);
    }
}

bool sound::checkSound()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (x > POS_X && x < POS_X + getWidth() &&
        y > POS_Y && y < POS_Y + getHeight())
    {
        isPlay = !isPlay;
        return true;
    }
    return false;
}