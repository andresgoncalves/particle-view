find_package(Qt6 REQUIRED COMPONENTS
  Gui
)

add_library(models STATIC
  Particle.cpp
)

target_link_libraries(models PRIVATE
  Qt6::Gui
)