cmake_minimum_required(VERSION 3.7)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
set(THREADS_PREFER_PTHREAD_FLAG ON)

project(Asteroids)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(Threads REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} src include media)

add_executable(Asteroids 
src/asteroid.cpp
src/controller.cpp
src/game.cpp 
src/main.cpp 
src/renderer.cpp
src/spaceobject.cpp
src/spaceship.cpp
)

string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(Asteroids 
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    Threads::Threads
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/media/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
