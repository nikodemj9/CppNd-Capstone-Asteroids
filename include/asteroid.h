#pragma once
#include "spaceobject.h"

class Asteroid : public SpaceObject {
public:
    Asteroid();
    Asteroid(float x, float y, float angle, float speed);
    void Simulate() override {Move();};
    void SetSize(int size);
    static SDL_Texture* texture;

};