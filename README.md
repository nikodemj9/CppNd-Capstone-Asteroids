# CppNd-Capstone-Asteroids
Simple game inspired by classic Atari's Asteroids. Done as final project of Udacity C++ Nanodegree program.  

\
Based on Udacity's CppND-Capstone-Snake-Game project 
* https://github.com/udacity/CppND-Capstone-Snake-Game


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

## UDACITY Review description

### File and class structure
Each class has its own *.cpp and *.h file. Header files are located in "include" directory for clarity.  
Three main classes are borrowed from CppND-Capstone-Snake-Game project:
* Renderer - responsible for image rendering,
* Controller - responsible for control input,
* Game - holds ownership of game elements.

Base class for on-screen objects is "SpaceObject", which is an abstract class with pure virtual method.
Derived classes are: Asteroid, Rocket, Spaceship which implements parameters and behaviour specific to these objects. Some of them seems rather simple and it could be reasonable to use SpaceObject class, but that would make future improvements much harder.  

Last one is "Sound" class which holds everything related to sound processing. Object of the class is used as a member of "Game".

### Expected behaviour of the program
Game allows to control the spaceship (movement, rotation) and shoot rockets from the ship.  
Asteroids are generated in random way on the edges of the screen.   
Shooting an asteroid gives you point.  
Being "shot" by an asteroid resets the game (and the score).  

### Rubric points
#### The project demonstrates an understanding of C++ functions and control structures.
Methods and arguments are named to clearly indicate their purpose.  
#### The project reads data from a file and process the data, or the program writes data to a file.
* renderer.cpp - lines 36 - 39
* sound.cpp - lines 28 - 31
#### The project accepts user input and processes the input.  
* controller.cpp - lines 27 - 54  
#### The project uses Object Oriented Programming techniques.
Except some starting parameters (screen resolution etc.) everything is stored in classes.
#### Classes use appropriate access specifiers for class members.
Present in all classes. SpaceObject class uses all three specifiers.
#### Class constructors utilize member initialization lists.
* asteroid.cpp - line 5
* game.cpp - lines 5 - 13
* renderer.cpp - lines 9 - 10
* rocket.cpp - line 6
* spaceobject.cpp - line 7
* spaceship.cpp - line 11
#### Classes encapsulate behavior.
* SpaceObject - methods: X(), Y(), Box(), Angle(), Move();
#### Classes follow an appropriate inheritance hierarchy.
SpaceObject contains typical methods and members such as Move(), x, y, Box etc.  
Method Simulate() is marked as pure virtual and deriving classes uses "override" keyword.
#### Overloaded functions allow the same function to operate on different parameters.
* Renderer class, method Render which can accept unique_pointer, vector of unique pointers or operate without argument to perform actual screen rendering. 
#### Derived class functions override virtual base class functions.
All classes derived from SpaceObject overrides Simulate() method. Usually it's just invoking Move() method, but it leaves place for future improvement. Like modyfing speed/trajectory of rockets or splitting large asteroids into smaller one.
#### Templates generalize functions in the project.
* game.h - lines 50 - 61,
* renderer.h - lines 29 - 38,
#### The project makes use of references in function declarations.
* controller.h - line 17, Shoot method uses reference to the vector,
* game.h - line 18, Run method uses references to controller and renderer,
* game.h - line 22, Render method uses reference to renderer,
* game.h - line 24, Simulate method uses references to the vectors,
* renderer.h - line 15, Render method uses reference to the vector,
* renderer.h - line 16, Render method uses reference to the unique_ptr,
#### The project uses destructors appropriately.
* renderer.cpp - lines 43 - 57, destroying SDL_image's library variables,
* sound.cpp - lines 17 - 24, destroying SDL_mixer's library variables,
#### The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
* spaceobject.cpp - method Move uses std::lock_guard for locking the resources, unlocking is done when the method runs out of scope,
* spaceship.cpp - methods Rotate and Accelerate, usage of std::lock_guard,
#### The project follows the Rule of 5.
Not implemented
#### The project uses move semantics to move data, instead of copying it, where possible.
Not implemented  
#### The project uses smart pointers instead of raw pointers.
* game.h - lines 33 - 35, unique pointers used for all on-screen objects to ensure proper deleting of the objects,
* Raw pointers used for SDL2 library's variables as they need appropriate method for freeing memory.
#### The project uses multithreading.
* game.cpp - line 15, thread for creating Asteroids, joined in Game desctructor,
* game.cpp - lines 88 - 95, threads for moving on-screen objects,
#### A promise and future is used in the project.
Not implemented
#### A mutex or lock is used in the project.
* game.cpp - line 88, locks asteroids vector,
* game.cpp - line 180, locks asteroids vector,
#### A condition variable is used in the project.
Not implemented

### Licensed resources used for project
* Spaceship model (CC BY 3.0) https://opengameart.org/content/night-raider
* Asteroid model (CC BY 4.0) https://opengameart.org/content/brown-asteroid
* Sounds by LittleRobotSoundFactory (CC) https://freesound.org/people/LittleRobotSoundFactory/