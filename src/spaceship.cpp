#include "spaceship.h"



Spaceship::Spaceship() : x(100), y(100), angle(0)
{

}

Spaceship::Spaceship(float x, float y, float angle) : x(x), y(y), angle(angle)
{

}

Rocket Spaceship::Shoot()
{
    Rocket rocket{x, y, angle, rockets_speed};
    return rocket;
}