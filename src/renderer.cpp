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

  // Load ship texture
  std::string filepath = "spaceship.png";

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( filepath.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", filepath.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        ship_texture = SDL_CreateTextureFromSurface( sdl_renderer, loadedSurface );
		if( ship_texture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", filepath.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

  // Load sky texture
  filepath = "nightsky.png";

	//Load image at specified path
	loadedSurface = IMG_Load( filepath.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", filepath.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        sky_texture = SDL_CreateTextureFromSurface( sdl_renderer, loadedSurface );
		if( sky_texture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", filepath.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}


}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Spaceship *spaceship) {
  SDL_Rect block;
  block.w = screen_width / 20;
  block.h = screen_height / 20;
  

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render background
  SDL_RenderCopy(sdl_renderer, sky_texture, NULL, NULL);

  // Render Ship
  // TODO get texture, rotate
  block.x = spaceship->X();
  block.y = spaceship->Y();
  while (block.x > screen_width) { block.x -= screen_width;};
  while (block.x < 0) { block.x += screen_width;};
  while (block.y > screen_width) { block.y -= screen_height;};
  while (block.y < 0) { block.y += screen_height;};
  SDL_RenderCopyEx(sdl_renderer, ship_texture, NULL, &block, spaceship->Angle(), NULL, SDL_FLIP_NONE);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
