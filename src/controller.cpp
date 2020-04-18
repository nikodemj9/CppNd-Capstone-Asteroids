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

void Controller::Shoot(Spaceship *spaceship)
{
    spaceship->Shoot();
}

void Controller::HandleInput(bool &running, Spaceship *spaceship) const {

  while (SDL_PollEvent(event.get()))
  {
  if (event->type == SDL_QUIT) 
  {
      running = false;
  } 
  else if(event->type == SDL_KEYDOWN || event->type == SDL_KEYUP)
  {
    // Move centerpoint of rotation for one of the trees:
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
          spaceship->Shoot();
    }
  }
  }
}