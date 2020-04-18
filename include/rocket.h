#pragma once
#include "spaceobject.h"


class Rocket : public SpaceObject {
    public:
        Rocket(float x, float y, float angle, float speed);

        void Simulate() override;

};