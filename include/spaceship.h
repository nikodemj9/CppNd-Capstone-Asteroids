#pragma once

#include "spaceobject.h"
#include "rocket.h"
#include <memory>
#include <vector>


class Spaceship : public SpaceObject {
    public:
        Spaceship();
        Spaceship(float x, float y, float angle);
        void Simulate() override;
        void Rotate(bool rotation);
        void Accelerate(bool acceleration);
        void Shoot();
        void Float();
        static SDL_Texture* texture;
        std::vector<std::unique_ptr<Rocket>> rockets;

    private:
        const float max_speed{400};
        const float acceleration{300};
        const float angular_acc{300};
        const float inertia{2};
        const float rockets_speed{600};

};

