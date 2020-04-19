#include "asteroid.h"

SDL_Texture* Asteroid::texture = NULL;

Asteroid::Asteroid(float x, float y, float angle, float speed) : SpaceObject(x, y, angle, speed)
{
    hitbox.w = 50;
    hitbox.h = 50;
    speed = speed;
}

void Asteroid::SetSize(int size)
{
    hitbox.w = hitbox.h = size;
}