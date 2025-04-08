find_package(Qt6 REQUIRED COMPONENTS
  Gui
)

add_library(loaders STATIC
  CustomLoader.cpp
)

target_link_libraries(loaders PRIVATE
  Qt6::Gui
)