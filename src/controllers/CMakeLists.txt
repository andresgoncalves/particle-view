find_package(Qt6 REQUIRED COMPONENTS
  Gui
)

add_library(controllers STATIC
  RenderController.cpp
  TransformController.cpp
)

target_link_libraries(controllers PRIVATE
  Qt6::Gui
)