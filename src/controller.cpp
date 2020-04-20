#include "controller.h"
#include <iostream>

Controller::Controller ()
{
  keyboard_state_array = SDL_GetKeyboardState(NULL);
  event = std::make_unique<SDL_Event>();
}

void Controller::ChangeRotation(Spaceship *spaceship, bool positive) const
{
    spaceship->Rotate(positive);
}

void Controller::ChangeSpeed(Spaceship *spaceship, bool positive) const
{
    spaceship->Accelerate(positive);
}

void Controller::Shoot(Spaceship *spaceship, std::vector<std::unique_ptr<Rocket>> &rockets)
{
    rockets.push_back(spaceship->Shoot());
}

void Controller::HandleInput(bool &running, Spaceship *spaceship, std::vector<std::unique_ptr<Rocket>> &rockets) {

      while(SDL_PollEvent(event.get()))
      {
            if (event->type == SDL_QUIT) 
            {
                  running = false;
            }
      }
   
      if (keyboard_state_array[SDL_SCANCODE_UP])
      {
            ChangeSpeed(spaceship, true);
      }
      if (keyboard_state_array[SDL_SCANCODE_DOWN])
      {
            ChangeSpeed(spaceship, false);
      }
      if (keyboard_state_array[SDL_SCANCODE_LEFT])
      {
            ChangeRotation(spaceship, false);
      }
      if (keyboard_state_array[SDL_SCANCODE_RIGHT])
      {
            ChangeRotation(spaceship, true);
      }
      if (keyboard_state_array[SDL_SCANCODE_SPACE])
      {
            Shoot(spaceship, rockets);
      }
                 
   
}