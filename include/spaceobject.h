#pragma once
#include <mutex>
#include <chrono>
#include "SDL.h"

class SpaceObject {

public:
    void Move();
    bool OnScreen(int const &screen_width, int const &screen_height) const;
    void NormalizePosition(int const &screen_width, int const &screen_height);
    virtual void Simulate() = 0;
    float X() {return hitbox.x;};
    float Y() {return hitbox.y;};
    SDL_Rect* Box() { return &hitbox;};
    float Angle() { return angle;};

protected:
    SpaceObject(float x, float y, float angle, float speed);
    float x,y;
    float angle;
    float speed;
    SDL_Rect hitbox;
    std::mutex pos_mtx, ang_mtx, speed_mtx;
    std::chrono::time_point<std::chrono::system_clock> last_update;
    std::chrono::duration<double> duration;
    
private:
    void UpdateHitbox();
};