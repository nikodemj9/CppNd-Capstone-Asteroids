#pragma once

#include <vector>
#include <memory>
#include "SDL.h"
#include "spaceship.h"
#include "asteroid.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();
  void ClearScreen();
  template<typename T>
  void Render(typename std::vector<std::unique_ptr<T>> &t);
  void Render(std::unique_ptr<Spaceship> &spaceship);
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
void Renderer::Render(typename std::vector<std::unique_ptr<T>> &t) {


    for (auto &object : t)
    {
        SDL_RenderCopyEx(sdl_renderer, object.get()->texture, NULL, object.get()->Box(), object.get()->Angle(), NULL, SDL_FLIP_NONE);
    }

}