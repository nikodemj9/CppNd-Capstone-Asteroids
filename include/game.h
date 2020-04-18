#pragma once
#include <memory>
#include <random>
#include <vector>
#include <thread>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "spaceship.h"
#include "asteroid.h"

class Game {
    public:
        Game(std::size_t grid_width, std::size_t grid_height);
        void Run(Controller const &controller, Renderer &renderer,
        std::size_t target_frame_duration);
        int GetScore() const;
        void Update();
        void Render(Renderer &renderer);
    private:
        void PlaceAsteroid();
        std::unique_ptr<Spaceship> spaceship;
        std::vector<std::unique_ptr<Asteroid>> asteroids;
        std::vector<std::unique_ptr<Rocket>> rockets;
        int score{0};
        std::random_device dev;
        std::mt19937 engine;
        std::uniform_int_distribution<int> random_w;
        std::uniform_int_distribution<int> random_h;  
        std::uniform_int_distribution<int> random_v;  

};

