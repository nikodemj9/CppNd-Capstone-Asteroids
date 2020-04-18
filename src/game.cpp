#include "game.h"

Game::Game(std::size_t screen_width, std::size_t screen_height)
    : spaceship(std::make_unique<Spaceship>(screen_width/2, screen_height/2, 0)),
      screen_width(screen_width),
      screen_height(screen_height),
      engine(dev()),
      random_w(0, static_cast<int>(screen_width)),
      random_h(0, static_cast<int>(screen_height))    
{
    PlaceAsteroid();
}

void Game::Run(Controller &controller, Renderer &renderer,
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
        controller.HandleInput(running, spaceship.get(), rockets);
        Update();
        Render(renderer);

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

void Game::Render(Renderer &renderer) {
    renderer.ClearScreen();
    renderer.Render(spaceship.get());
    for (auto &asteroid : asteroids)
    {
        renderer.Render(asteroid.get());
    }
    for (auto &rocket : rockets)
    {
        renderer.Render(rocket.get());
    }
    renderer.Render();
}

void Game::Update() {

    PlaceAsteroid();

    std::vector<std::thread> moving_objects;

    moving_objects.emplace_back(std::thread(&Spaceship::Simulate,spaceship.get()));

    for (auto it = asteroids.begin(); it != asteroids.end(); it++)
    {   
        if (it->get()->OnScreen(screen_width, screen_height)){
        moving_objects.emplace_back(std::thread(&Asteroid::Move,it->get()));
        }
        else
        {
            asteroids.erase(it);
            it--;
        }
        
    }


    for (auto it = rockets.begin(); it != rockets.end(); it++)
    {
        if (it->get()->OnScreen(screen_width, screen_height)){
        moving_objects.emplace_back(std::thread(&Rocket::Move,it->get()));
        }
        else
        {
            rockets.erase(it);
            it--;
        }
    }

    for (auto &thread : moving_objects)
    {
        thread.join();
    }

    // Check hitboxes???

}

int Game::GetScore() const { return score; }

void Game::PlaceAsteroid()
{
    // calculate random x or y, set another coordinate to 0
    // calculate speed
    // create asteroid on heap, move to vector

    // Test one
    if (score < 2){
    asteroids.emplace_back(std::make_unique<Asteroid>(10, 10, 45, 2));
    score++;
    }

    
}