#pragma once
#include <memory>
#include <random>
#include <vector>
#include <thread>
#include <algorithm>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "spaceship.h"
#include "asteroid.h"
#include "sound.h"

class Game {
    public:
        Game(std::size_t screen_width, std::size_t screen_height);
        ~Game();
        void Run(Controller &controller, Renderer &renderer,
        std::size_t target_frame_duration);
        void Update();
        void Reset();
        void Render(Renderer &renderer);
        template <typename T>
        void Simulate(typename std::vector<std::unique_ptr<T>> &objects, std::vector<std::thread> &threads);
        int GetScore()  const;
    private:
        void PlaceAsteroid();
        Sound sound;
        bool running;
        int score{0};
        std::size_t rockets_amount{0};
        std::size_t screen_width, screen_height;
        std::unique_ptr<Spaceship> spaceship;
        std::vector<std::unique_ptr<Asteroid>> asteroids;
        std::random_device dev;
        std::mt19937 engine;
        std::uniform_int_distribution<int> random_screen;
        std::uniform_int_distribution<int> random_w;
        std::uniform_int_distribution<int> random_h;  
        std::uniform_int_distribution<int> random_speed;
        std::uniform_int_distribution<int> random_angle;
        std::thread asteroid_spawner;
        std::mutex asteroids_lock;
        

};

// Simulates space objects, removes if they are out of the screen
template <typename T>
void Game::Simulate(typename  std::vector<std::unique_ptr<T>> &objects, std::vector<std::thread> &threads)
{
    // Erase elements that are out of the screen
    auto end = std::remove_if(objects.begin(), objects.end(), [this](std::unique_ptr<T> &i){ return !(i->OnScreen(screen_width, screen_height));} );
    objects.erase(end, objects.end());
    // Simulate remaining objects 
    for (auto it = objects.begin(); it != objects.end(); it++)
    {   
        threads.emplace_back(std::thread(&T::Simulate,it->get()));
    }  
}