#pragma once

#include "spaceship.h"

class Controller {
 public:
  void HandleInput(bool &running, Spaceship *spaceship) const;

 private:
  void ChangeRotation(Spaceship *spaceship, bool positive) const;
  void ChangeSpeed(Spaceship *spaceship, bool positive) const;
  void Shoot(Spaceship *spaceship);
            
};

