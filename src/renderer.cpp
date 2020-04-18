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
  ship_texture = IMG_LoadTexture(sdl_renderer, "spaceship.png");
  sky_texture = IMG_LoadTexture(sdl_renderer, "nightsky.png");
  rocket_texture = IMG_LoadTexture(sdl_renderer, "rocket.png");
 
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_DestroyRenderer(sdl_renderer);
  SDL_DestroyTexture(ship_texture);
  SDL_DestroyTexture(sky_texture);
  SDL_DestroyTexture(rocket_texture);
  SDL_Quit();
}

void Renderer::ClearScreen() {

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render background
  SDL_RenderCopy(sdl_renderer, sky_texture, NULL, NULL);
}

void Renderer::Render(Spaceship *spaceship) {

  
  // Render Ship
  spaceship->NormalizePosition(screen_width, screen_height);
  SDL_RenderCopyEx(sdl_renderer, ship_texture, NULL, spaceship->Box(), spaceship->Angle(), NULL, SDL_FLIP_NONE);
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::Render(Rocket *rocket) {

  // Render Rocket
  SDL_RenderCopyEx(sdl_renderer, rocket_texture, NULL, rocket->Box(), rocket->Angle(), NULL, SDL_FLIP_NONE);
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::Render(Asteroid *asteroid)
{

}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
