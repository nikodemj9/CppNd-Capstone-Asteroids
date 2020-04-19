#pragma once
#include <memory>
#include <random>
#include <vector>
#include <thread>
#include <thread>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "spaceship.h"
#include "asteroid.h"

class Game {
    public:
        Game(std::size_t screen_width, std::size_t screen_height);
        ~Game();
        void Run(Controller &controller, Renderer &renderer,
        std::size_t target_frame_duration);
        int GetScore() const;
        void Update();
        void Render(Renderer &renderer);
        template <typename T>
        void Simulate(typename std::vector<std::unique_ptr<T>> &objects, std::vector<std::thread> &threads);
    private:
        bool running;
        std::size_t screen_width, screen_height;
        void PlaceAsteroid();
        std::unique_ptr<Spaceship> spaceship;
        std::vector<std::unique_ptr<Asteroid>> asteroids;
        std::vector<std::unique_ptr<Rocket>> rockets;
        int score{0};
        std::random_device dev;
        std::mt19937 engine;
        std::uniform_int_distribution<int> random_screen;
        std::uniform_int_distribution<int> random_w;
        std::uniform_int_distribution<int> random_h;  
        std::uniform_int_distribution<int> random_speed;
        std::uniform_int_distribution<int> random_angle;
        std::thread asteroid_spawner;
        

};

// Simulates space objects, removes if they are out of the screen
template <typename T>
void Game::Simulate(typename  std::vector<std::unique_ptr<T>> &objects, std::vector<std::thread> &threads)
{
      for (auto it = objects.begin(); it != objects.end(); it++)
    {   
        if (it->get()->OnScreen(screen_width, screen_height)){
             threads.emplace_back(std::thread(&T::Simulate,it->get()));
        }
        else
        {
            objects.erase(it);
            it--;
        }   
    }  
}