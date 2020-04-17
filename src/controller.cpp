#include "controller.h"
#include <iostream>
#include "SDL.h"


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
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeSpeed(spaceship, true);
          break;
        case SDLK_DOWN:
          ChangeSpeed(spaceship, false);
          break;
        case SDLK_LEFT:
          ChangeRotation(spaceship, false);
          break;
        case SDLK_RIGHT:
          ChangeRotation(spaceship, true);
          break;
        case SDLK_SPACE:
          spaceship->Shoot();
          break;
      }
    }
  }
}