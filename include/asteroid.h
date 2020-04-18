#pragma once
#include "spaceobject.h"

class Asteroid : public SpaceObject {
public:
    Asteroid();
    Asteroid(float x, float y, float angle, float speed);
    void Simulate() {Move();};
    void SetSize(int size);
};