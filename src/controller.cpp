#include "controller.h"
#include <iostream>

Controller::Controller () :
      buttonArrowLeft(std::make_unique<RotateLeftCommand>()),
      buttonArrowRight(std::make_unique<RotateRightCommand>()),
      buttonArrowUp(std::make_unique<AccelerateCommand>()),
      buttonArrowDown(std::make_unique<DecelarateCommand>()),
      buttonSpace(std::make_unique<ShootCommand>())
{
  keyboard_state_array = SDL_GetKeyboardState(NULL);
  event = std::make_unique<SDL_Event>();
}

void Controller::HandleInput(bool &running, Spaceship *spaceship) {

      while(SDL_PollEvent(event.get()))
      {
            if (event->type == SDL_QUIT) 
            {
                  running = false;
            }
      }
   
      if (keyboard_state_array[SDL_SCANCODE_UP])
      {
            buttonArrowUp->execute(spaceship);
      }
      if (keyboard_state_array[SDL_SCANCODE_DOWN])
      {
            buttonArrowDown->execute(spaceship);
      }
      if (keyboard_state_array[SDL_SCANCODE_LEFT])
      {
            buttonArrowLeft->execute(spaceship);
      }
      if (keyboard_state_array[SDL_SCANCODE_RIGHT])
      {
            buttonArrowRight->execute(spaceship);
      }
      if (keyboard_state_array[SDL_SCANCODE_SPACE])
      {
            buttonSpace->execute(spaceship);
      }
                 
   
}