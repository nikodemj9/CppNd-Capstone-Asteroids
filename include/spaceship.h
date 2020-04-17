#pragma once
#include "spaceobject.h"

class Rocket : public SpaceObject {
    public:
        Rocket(float x, float y, float angle, float speed);
        void Simulate() override;

};

class Spaceship : public SpaceObject {
    public:
        Spaceship();
        Spaceship(float x, float y, float angle);
        void Simulate() override;
        void Rotate(bool rotation);
        void Accelerate(bool acceleration);
        Rocket Shoot();
        void Float();

    private:
        const float acceleration{0.001};
        const float angular_acc{0.1};
        const float inertia{0.001};
        const float rockets_speed{0.1};
};