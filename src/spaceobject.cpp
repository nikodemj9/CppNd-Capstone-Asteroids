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

bool SpaceObject::OnScreen(int const &screen_width, int const &screen_height) const
{
    return (x > 0 && x < screen_width && y > 0 && y < screen_height );
}

void SpaceObject::NormalizePosition(int const &screen_width, int const &screen_height)
{
  while (x > screen_width) { x -= screen_width;};
  while (x < 0) { x += screen_width;};
  while (y > screen_width) { y -= screen_height;};
  while (y < 0) { y += screen_height;};
}