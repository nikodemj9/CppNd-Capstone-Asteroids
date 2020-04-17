#pragma once

class Rocket {
    public:
        Rocket(float x, float y, float angle, float speed);
    private:
        float angle;
        float x,y;
        float speed;
};

class Spaceship {

    Spaceship();
    Spaceship(float x, float y, float angle);
    Rocket Shoot();

    private:
        float angle;
        float x, y;
        const float rockets_speed{0.1};
};