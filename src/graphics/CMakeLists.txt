find_package(Qt6 REQUIRED COMPONENTS
  OpenGL
)

add_library(graphics STATIC

  renderers/SceneRenderer.cpp
  renderers/ParticleRenderer.cpp
  renderers/VectorRenderer.cpp
  renderers/AxesRenderer.cpp
  renderers/ColorScaleRenderer.cpp
  renderers/ContainerRenderer.cpp

  shapes/ArrowFactory.cpp
  shapes/SphereFactory.cpp
  shapes/CubeFactory.cpp

  shaders/GenericShader.cpp
)

target_link_libraries(graphics PRIVATE
  Qt6::OpenGL
)