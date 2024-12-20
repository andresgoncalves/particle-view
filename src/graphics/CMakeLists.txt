find_package(Qt6 REQUIRED COMPONENTS
  OpenGL
)

add_library(graphics STATIC
  AxisRenderer.cpp
  ParticleRenderer.cpp
  SceneRenderer.cpp
)

target_link_libraries(graphics PRIVATE
  Qt6::OpenGL
)