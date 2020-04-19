#pragma once

#include <vector>
#include "SDL.h"
#include "spaceship.h"
#include "asteroid.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();
  void ClearScreen();
  template<typename T>
  void Render(T *t);
  void Render();
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  SDL_Texture* sky_texture;

  const std::size_t screen_width;
  const std::size_t screen_height;
};

template <typename T>
void Renderer::Render(T *t) {
  SDL_RenderCopyEx(sdl_renderer, t->texture, NULL, t->Box(), t->Angle(), NULL, SDL_FLIP_NONE);
}