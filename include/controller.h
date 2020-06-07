#pragma once

#include "spaceship.h"
#include "SDL.h"
#include <memory>
#include <vector>
#include <memory>

class Controller {
 public:
  Controller ();
  void HandleInput(bool &running, Spaceship *spaceship);

 private:
  void ChangeRotation(Spaceship *spaceship, bool positive) const;
  void ChangeSpeed(Spaceship *spaceship, bool positive) const;
  void Shoot(Spaceship *spaceship);
  const Uint8 *keyboard_state_array;
  std::unique_ptr<SDL_Event> event;
 
};

