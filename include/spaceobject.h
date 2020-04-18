#pragma once
#include <mutex>

class SpaceObject {

public:
    void Move();
    bool OnScreen(int const &screen_width, int const &screen_height) const;
    void NormalizePosition(int const &screen_width, int const &screen_height);
    virtual void Simulate() = 0;
    float X() {return x;};
    float Y() {return y;};
    float Angle() { return angle;};

protected:
    SpaceObject(float x, float y, float angle, float speed);
    float x,y;
    float angle;
    float speed;
    std::mutex pos_mtx, ang_mtx, speed_mtx;

};