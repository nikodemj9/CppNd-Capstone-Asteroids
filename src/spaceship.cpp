#include "spaceship.h"
#include <cstdlib>
#include <chrono>
#include <thread>


Spaceship::Spaceship() : SpaceObject(100, 100, 0, 0)
{

}

Spaceship::Spaceship(float x, float y, float angle) : SpaceObject(x, y, angle, 0)
{

}

void Spaceship::Rotate(bool positive)
{
    std::lock_guard<std::mutex> lock(ang_mtx);
    angle = positive ? angle + angular_acc : angle - angular_acc;
}

void Spaceship::Accelerate(bool positive)
{
    std::lock_guard<std::mutex> lock(speed_mtx);
    speed = positive ? speed + acceleration : speed - acceleration;
}

std::unique_ptr<Rocket> Spaceship::Shoot()
{
    return std::make_unique<Rocket>(x, y, angle, rockets_speed+speed);
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