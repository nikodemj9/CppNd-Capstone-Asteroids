# CppNd-Capstone-Asteroids
Simple game inspired by classic Atari's Asteroids. Done as final project of Udacity C++ Nanodegree program.

Based on Udacity's CppND-Capstone-Snake-Game project 

https://github.com/udacity/CppND-Capstone-Snake-Game


<img src="asteroids.gif"/>


## Build & run manual
```
sudo apt install libsdl2-image-* libsdl2-mixer*
git clone --recurse-submodules https://github.com/nikodemj9/CppNd-Capstone-Asteroids.git
cd CppNd-Capstone-Asteroids
mkdir build && cd build
cmake .. && make -j4
./Asteroids
```

## Controls
```
UP = Accelerate
DOWN = Brake
LEFT, RIGHT = Rotate
SPACE = Shoot
```

## Description



### Licensed resources used for project
* Spaceship model (CC BY 3.0) https://opengameart.org/content/night-raider
* Asteroid model (CC BY 4.0) https://opengameart.org/content/brown-asteroid
* Sounds by LittleRobotSoundFactory (CC) https://freesound.org/people/LittleRobotSoundFactory/