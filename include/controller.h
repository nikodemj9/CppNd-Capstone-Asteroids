#pragma once

#include "spaceship.h"
#include "command.h"
#include "SDL.h"
#include <memory>
#include <vector>
#include <memory>

class Controller {
 public:
  Controller ();
  void HandleInput(bool &running, Spaceship *spaceship);

 private:
  std::unique_ptr<Command> buttonArrowUp;
  std::unique_ptr<Command> buttonArrowDown;
  std::unique_ptr<Command> buttonArrowLeft;
  std::unique_ptr<Command> buttonArrowRight;
  std::unique_ptr<Command> buttonSpace;
  const Uint8 *keyboard_state_array;
  std::unique_ptr<SDL_Event> event;
 
};

