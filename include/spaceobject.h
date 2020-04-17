#pragma once
#include <mutex>

class SpaceObject {

public:
    void Move();
    virtual void Simulate() = 0;
    float X() {return x;};
    float Y() {return y;};

protected:
    SpaceObject(float x, float y, float angle, float speed);
    float x,y;
    float angle;
    float speed;
    std::mutex pos_mtx, ang_mtx, speed_mtx;
};