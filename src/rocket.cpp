#include "rocket.h"

Rocket::Rocket(float x, float y, float angle, float speed)
    : SpaceObject(x, y, angle, speed)
{
    hitbox.w = 10;
    hitbox.h = 4;
}

void Rocket::Simulate()
{
    
}