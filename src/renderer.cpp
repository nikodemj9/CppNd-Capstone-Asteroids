#include "renderer.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height)
    : screen_width(screen_width),
      screen_height(screen_height){
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Asteroids Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
  

  IMG_Init(IMG_INIT_PNG);
  Spaceship::texture = IMG_LoadTexture(sdl_renderer, "media/spaceship.png");
  sky_texture = IMG_LoadTexture(sdl_renderer, "media/nightsky.png");
  Rocket::texture = IMG_LoadTexture(sdl_renderer, "media/rocket.png");
  Asteroid::texture = IMG_LoadTexture(sdl_renderer, "media/asteroid.png");
 
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_DestroyRenderer(sdl_renderer);
  SDL_DestroyTexture(sky_texture);
  SDL_DestroyTexture(Spaceship::texture);
  SDL_DestroyTexture(Rocket::texture);
  SDL_DestroyTexture(Asteroid::texture);
  sdl_window = NULL;
  sdl_renderer = NULL;
  sky_texture = NULL;
  Spaceship::texture = NULL;
  Rocket::texture = NULL;
  Asteroid::texture = NULL;
  SDL_Quit();
}

void Renderer::ClearScreen() {

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render background
  SDL_RenderCopy(sdl_renderer, sky_texture, NULL, NULL);
}

void Renderer::Render(std::unique_ptr<Spaceship> &spaceship)
{
  SDL_RenderCopyEx(sdl_renderer, spaceship.get()->texture, NULL, spaceship.get()->Box(), spaceship.get()->Angle(), NULL, SDL_FLIP_NONE);
}


void Renderer::Render()
{
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}


void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
