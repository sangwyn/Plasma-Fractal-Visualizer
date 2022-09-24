cmake_minimum_required(VERSION 3.23)
project(plasma_fractal)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(plasma_fractal main.cpp Globals.h FractalGenerator.cpp FractalGenerator.h Globals.cpp)

target_link_libraries(plasma_fractal sfml-graphics sfml-audio)