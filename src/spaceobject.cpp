#include "spaceobject.h"
#include <cmath>

#define deg2rad 0.0174532925 

SpaceObject::SpaceObject(float x, float y, float angle, float speed) :
    angle(angle), speed(speed), x(x), y(y) {
        hitbox.x = x;
        hitbox.y = y;
        last_update = std::chrono::system_clock::now();
    };

void SpaceObject::Move()
{
    std::lock_guard<std::mutex> locks(speed_mtx);
    std::lock_guard<std::mutex> locka(ang_mtx);
    std::lock_guard<std::mutex> lockp(pos_mtx);
    duration = std::chrono::system_clock::now() - last_update;
    x += std::cos(angle * deg2rad) * speed * duration.count();
    y += std::sin(angle * deg2rad) * speed * duration.count();
    UpdateHitbox();
    last_update = std::chrono::system_clock::now();
}

bool SpaceObject::OnScreen(int const &screen_width, int const &screen_height) const
{
    return (hitbox.x >= 0 && hitbox.x <= screen_width && hitbox.y >= 0 && hitbox.y <= screen_height );
}

void SpaceObject::NormalizePosition(int const &screen_width, int const &screen_height)
{
    while (x > screen_width) { x -= screen_width;};
    while (x < 0) { x += screen_width;};
    while (y > screen_width) { y -= screen_height;};
    while (y < 0) { y += screen_height;};
    UpdateHitbox();
}

void SpaceObject::UpdateHitbox()
{
    hitbox.x = std::round(x);
    hitbox.y = std::round(y);
}

