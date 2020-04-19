#pragma once
#include "spaceobject.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Rocket : public SpaceObject {
public:
    Rocket(float x, float y, float angle, float speed);
    void Simulate() override;
    static SDL_Texture* texture;

};