#include "game.h"
#include <chrono>

Game::Game(std::size_t screen_width, std::size_t screen_height)
    : spaceship(std::make_unique<Spaceship>(screen_width/2, screen_height/2, 0)),
      screen_width(screen_width),
      screen_height(screen_height),
      engine(dev()),
      random_screen(0,3),
      random_w(0, static_cast<int>(screen_width)),
      random_h(0, static_cast<int>(screen_height)),
      random_speed(200, 500),
      random_angle(3000, 15000)
{
    asteroid_spawner = std::thread(&Game::PlaceAsteroid, this);
}

Game::~Game ()
{
    running = false;
    asteroid_spawner.join();
}

void Game::Run(Controller &controller, Renderer &renderer,
        std::size_t target_frame_duration)
{
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    running = true;


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
    renderer.Render<Spaceship>(spaceship.get());
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

    // Count rockets
    if (rockets_amount != rockets.size())
    {
        sound.Play(sound.shoot);
        rockets_amount = rockets.size();
    }
    // Move all objects
    std::vector<std::thread> moving_objects;
    moving_objects.emplace_back(std::thread(&Spaceship::Simulate,spaceship.get()));
    Simulate(asteroids, moving_objects);
    Simulate(rockets, moving_objects);
    for (auto &thread : moving_objects)
    {
        thread.join();
    }
    spaceship->NormalizePosition(screen_width, screen_height);

    // Check hitboxes
    for (auto &rocket : rockets)
    {
        for (auto it = asteroids.begin(); it != asteroids.end(); it++)
        {
            if (SDL_HasIntersection(rocket->Box(), it->get()->Box()))
            {
                asteroids.erase(it);
                it--;
                score++;
                sound.Play(sound.explosion);
            }
        }
    }
    // Check hitboxes for ship, reset game if hit
    bool reset;
    for (auto &asteroid : asteroids)
    {
        if (SDL_HasIntersection(asteroid->Box(), spaceship->Box()))
        {
            reset = true;
        }
    }
    if (reset) Reset();

}

void Game::Reset()
{
        spaceship.reset(new Spaceship(screen_width/2, screen_height/2, 0));
        score = 0;
        sound.Play(sound.death);
        asteroids.clear();
        rockets.clear();
}

int Game::GetScore() const { return score; }

void Game::PlaceAsteroid()
{   
    auto interval = std::chrono::milliseconds(1000);
    auto last_spawn = std::chrono::system_clock::now();
    int x,y;
    float angle, speed;
    while (running)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - last_spawn);

        if (elapsed > interval)
        {
            x = random_w(engine);
            y = 0;
            angle = static_cast<float>(random_angle(engine)) / 100.0;
            speed = static_cast<float>(random_speed(engine)) / 100.0;

            switch (random_screen(engine)){
                case 0: // Up
                    y = 0;
                    break;
                case 1: // Right
                    x = screen_width;
                    angle += 90;
                    break;
                case 2: // Down
                    y = screen_height;
                    angle += 180;
                    break;
                case 4: // Left
                    x = 0;
                    angle += 270;
                    break;
            }
            
            asteroids.emplace_back(std::make_unique<Asteroid>(x, y, angle, speed));
            last_spawn = std::chrono::system_clock::now();
        }
    }




}