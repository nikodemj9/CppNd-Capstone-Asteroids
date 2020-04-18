#pragma once

#include <vector>
#include "SDL.h"
#include "spaceship.h"
#include "asteroid.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();

  void Render(Spaceship *spaceship);
  void Render(Asteroid *asteroid);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  SDL_Texture* ship_texture;
  SDL_Texture* sky_texture;
  
  const std::size_t screen_width;
  const std::size_t screen_height;
};
