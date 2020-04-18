#include "spaceobject.h"
#include <cmath>

const double pi = std::acos(-1);

SpaceObject::SpaceObject(float x, float y, float angle, float speed) :
    angle(angle), speed(speed) {
        hitbox.x = x;
        hitbox.y = y;
    };

void SpaceObject::Move()
{
    std::lock_guard<std::mutex> locks(speed_mtx);
    std::lock_guard<std::mutex> locka(ang_mtx);
    std::lock_guard<std::mutex> lockp(pos_mtx);
    hitbox.x += std::cos(angle * (pi/180)) * speed;
    hitbox.y += std::sin(angle * (pi/180)) * speed;
}

bool SpaceObject::OnScreen(int const &screen_width, int const &screen_height) const
{
    return (hitbox.x > 0 && hitbox.x < screen_width && hitbox.y > 0 && hitbox.y < screen_height );
}

void SpaceObject::NormalizePosition(int const &screen_width, int const &screen_height)
{
  while (hitbox.x > screen_width) { hitbox.x -= screen_width;};
  while (hitbox.x < 0) { hitbox.x += screen_width;};
  while (hitbox.y > screen_width) { hitbox.y -= screen_height;};
  while (hitbox.y < 0) { hitbox.y += screen_height;};
}