#pragma once
#include "spaceobject.h"
#include "rocket.h"
#include <memory>


class Spaceship : public SpaceObject {
    public:
        Spaceship();
        Spaceship(float x, float y, float angle);
        void Simulate() override;
        void Rotate(bool rotation);
        void Accelerate(bool acceleration);
        std::unique_ptr<Rocket> Shoot();
        void Float();

    private:
        const float acceleration{0.1};
        const float angular_acc{5};
        const float inertia{0.01};
        const float rockets_speed{10};
};