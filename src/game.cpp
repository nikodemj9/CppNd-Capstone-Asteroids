#include "game.h"

Game::Game(std::size_t screen_width, std::size_t screen_height)
    : spaceship(std::make_unique<Spaceship>(screen_width/2, screen_height/2, 0)),
      engine(dev()),
      random_w(0, static_cast<int>(screen_width)),
      random_h(0, static_cast<int>(screen_height))    
{
    PlaceAsteroid();
}

void Game::Run(Controller const &controller, Renderer &renderer,
        std::size_t target_frame_duration)
{
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool running = true;

    while (running) {
        frame_start = SDL_GetTicks();

        // Input, Update, Render - the main game loop.
        controller.HandleInput(running, spaceship.get());
        Update();
        renderer.Render(spaceship.get());

        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000) {
            renderer.UpdateWindowTitle(score, frame_count);
            frame_count = 0;
            title_timestamp = frame_end;
        }

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }
    }

}

void Game::Update() {

    spaceship->Move();

    for (auto &asteroid : asteroids)
    {
        asteroid->Move();
    }

    // Check hitboxes???

}

int Game::GetScore() const { return score; }

void Game::PlaceAsteroid()
{
    // calculate random x or y, set another coordinate to 0
    // calculate speed
    // create asteroid on heap, move to vector
}