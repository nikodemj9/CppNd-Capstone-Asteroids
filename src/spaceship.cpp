#include "spaceship.h"
#include <cstdlib>
#include <chrono>
#include <thread>
#include <algorithm>

#include <iostream>

SDL_Texture* Spaceship::texture = NULL;

Spaceship::Spaceship() : SpaceObject(100, 100, 0, 0)
{
    hitbox.w = 50;
    hitbox.h = 50;
}

Spaceship::Spaceship(float x, float y, float angle) : SpaceObject(x, y, angle, 0)
{
    hitbox.w = 50;
    hitbox.h = 50;
}

void Spaceship::Rotate(bool positive)
{
    std::lock_guard<std::mutex> lock(ang_mtx);
    angle = positive ? angle + angular_acc * duration.count() : angle - angular_acc * duration.count();
}

void Spaceship::Accelerate(bool positive)
{
    std::lock_guard<std::mutex> lock(speed_mtx);
    speed = positive ? speed + acceleration * duration.count() : speed - acceleration * duration.count();
    speed = std::clamp(speed, -max_speed, max_speed); // Limit speed
    std::this_thread::sleep_for(std::chrono::milliseconds(1)); // Needed for std::clamp
}

std::unique_ptr<Rocket> Spaceship::Shoot()
{
    return std::make_unique<Rocket>(hitbox.x+(hitbox.w/2), hitbox.y+(hitbox.h/2), angle, rockets_speed+speed);
}

void Spaceship::Simulate()
{
    Move();
    Float();
}

void Spaceship::Float()
{
    if (std::abs(speed) > 0.02)
    {
        speed += speed > 0 ? -inertia : inertia;        
    }
    else
    {
        speed = 0;
    }
    
}