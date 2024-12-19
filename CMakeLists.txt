cmake_minimum_required(VERSION 3.10.0)
project(particle-view VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_PREFIX_PATH "build/Release/generators")


find_package(Qt6 REQUIRED COMPONENTS
  Gui
  Widgets
)

add_subdirectory(src/controllers)
add_subdirectory(src/graphics)
add_subdirectory(src/models)
add_subdirectory(src/widgets)

add_executable(main src/main.cpp)

target_link_libraries(main PRIVATE
  controllers
  graphics
  models
  widgets
)

target_link_libraries(main PRIVATE
  Qt6::Gui
  Qt6::Widgets
)