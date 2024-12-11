cmake_minimum_required(VERSION 3.10.0)
project(particle-view VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_PREFIX_PATH "build/Release/generators")

add_executable(main src/main.cpp)

