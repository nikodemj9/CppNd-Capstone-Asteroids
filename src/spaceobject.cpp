#include "spaceobject.h"
#include <cmath>

const double pi = std::acos(-1);

SpaceObject::SpaceObject(float x, float y, float angle, float speed) :
    x(x), y(y), angle(angle), speed(speed) {

    };

void SpaceObject::Move()
{
    std::lock_guard<std::mutex> locks(speed_mtx);
    std::lock_guard<std::mutex> locka(ang_mtx);
    std::lock_guard<std::mutex> lockp(pos_mtx);
    x += std::cos(angle * (pi/180)) * speed;
    y += std::sin(angle * (pi/180)) * speed;
}